/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ekinnune.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:10:42 by ekinnune          #+#    #+#             */
/*   Updated: 2023/06/19 14:52:31 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int token_type_command(t_token *token);
t_token *skip_i_token(t_token *token, int i);
int count_name(t_token *token);
int token_type_redir(t_token *token);
int count_redir(t_token *token);
int set_redir(t_command *command, t_token *token);
int set_name(t_command *command, t_token *token);
t_token *find_redir(t_token *token);
t_token	*skip_pipe(t_token *token);
t_command	*convert_tokens(t_token *token);
void print_commands(t_command *command);


int token_type_command(t_token *token)
{
	return (token->type == NAME |
				token->type == DQUOTE |
				token->type == SQUOTE |
				token->type == ENVAR |
				token->type == EXVAR);
}

t_token *skip_i_token(t_token *token, int i)
{
	if (token && i)
		return (skip_i_token(token->next, i - 1));
	return (token);
}

int count_name(t_token *token)
{
	if (!token)
		return (0);
	if (token_type_command(token))
	{
		return (1 + count_name(token->next));
	}
	else if (token_type_redir(token))
	{
		return (count_name(skip_i_token(token, count_redir(token))));
	}
	return (0);
}

int token_type_redir(t_token *token)
{
	return (token->type == RDIRIN |
				token->type == RDIROUT |
				token->type == RDIRAPP |
				token->type == RDIRDEL);
}

int count_redir(t_token *token)
{
	if (!token)
		return (0);
	if (token_type_redir(token))
	{
		if (token->next)
		{
			if (token_type_command(token->next))
				return (2 + count_redir(token->next->next));			
		}
		else
			return (0);
	}
	return (0);
}


int set_redir(t_command *command, t_token *token)
{
	t_token *temp;

	if (!token)
		return (0);
	if (token_type_redir(token))
	{
		if (token->next)
		{
			*(command->redir) = token->str;
			*(command->redir + 1) = token->next->str;
			command->redir += 2;
			return (2 + set_redir(command, token->next->next));
		}
		else //raise error, possibly exit
		{
			return (0);
		}
	}
	return (0);
}

int set_name(t_command *command, t_token *token)
{
	if (!token)
		return (0);
	if (token_type_command(token))
	{
		*(command->cmd) = token->str;
		command->cmd += 1;
		return (1 + set_name(command, token->next));
	}
	else if (token_type_redir(token))
		return (set_name(command, skip_i_token(token, count_redir(token))));
	return (0);
}

t_token *find_redir(t_token *token)
{
	if (!token)
		return (NULL);
	if (token->type == PIPE)
		return (NULL);
	if (token_type_redir(token))
		return (token);
	return (find_redir(token->next));
}

t_token	*skip_pipe(t_token *token)
{
	if (token)
	{
		if (token->type != PIPE)
			return (skip_pipe(token->next));
		else
			return (token->next);
	}
	return (token);
}

t_command	*convert_tokens(t_token *token)
{
	int i;
	t_command *command;
	t_token *test_token;

	if (!token)
		return (NULL);
	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	test_token = find_redir(token);
	i = count_redir(test_token);
	command->redir = malloc((sizeof(char *) * (i + 1)));
	*(command->redir + i) = NULL;
	i = set_redir(command, test_token);
	command->redir -= i;
	i = count_name(token);
	command->cmd = malloc((sizeof(char *) * (i + 1)));
	*(command->cmd + i) = NULL; 
	i = set_name(command, token);
	command->cmd -= i;
	command->next = convert_tokens(skip_pipe(token));
	return (command);
}

void print_commands(t_command *command)
{
	int i;
	if (!command)
	{
		return ;
	}
	i = 0;
	while(*(command->cmd + i))
	{
		printf("[%s]", *(command->cmd + i));
		i++;
	}
	printf("\n");
	i = 0;
	while(*(command->redir + i))
	{
		printf("{%s}", *(command->redir + i));
		i++;
	}
	printf("\n");
	print_commands(command->next);
}

int main(void)
{
	t_token *token;
	t_command *command;
	char *input;
	char *args[10] = {".", NULL};
	extern char	**environ;
	// print_environ();
	// run_command("ls", args);
	// printf("keeps going\n");
	// return (0);
	while (1)	
	{
		input = readline(">");
		// printf("[%s]\n", input);
		// list = build_commands(input);
		token = tokenizer(input);
		if (token)
		{
			// print_tokens(token);
			command = convert_tokens(token);
			execve(*(command->cmd), command->cmd + 1, environ);
			print_commands(command);
			// free_tokens(token);
		}
		// printf("[%d]\n", lst_size(list));
		// lst_print_args(list);
		// lst_free(list);
		if (input)
			free(input);
	}
	return (0);
}
