/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ekinnune.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:10:42 by ekinnune          #+#    #+#             */
/*   Updated: 2023/06/15 18:47:20 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_commands(t_command *command);

int token_type_command(t_token *token)
{
	return (token->type == NAME |
				token->type == DQUOTE |
				token->type == SQUOTE |
				token->type == ENVAR |
				token->type == EXVAR);
}

int count_names(t_token *token)
{
	int i;

	i = 0;
	if (!token)
		return (0);
	while (token_type_command(token))
	{
		token = token->next;
		i++;
		if (!token)
			break ;
	}
	return (i);
}

int token_type_redir(t_token *token)
{
	return (token->type == RDIRIN |
				token->type == RDIROUT |
				token->type == RDIRAPP |
				token->type == RDIRDEL);
}

int count_redirs(t_token *token)
{
	int i;

	i = 0;
	if (!token)
		return (0);
	// while (token_type_redir(token))
	while (token->type != PIPE)
	{
		token = token->next;
		i++;
		if (!token)
			break ;
	}
	return (i);
}

t_command	*convert_tokens(t_token *token)
{
	int i;
	t_command *command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	i = count_names(token);
	printf(",%d,\n", i);
	if (!i)
	{
		command->cmd = malloc(sizeof(char *));
		*(command->cmd) = NULL;
		return (command);
	}
	else
		command->cmd = malloc((sizeof(char *) * (i + 1)));
	while (token_type_command(token))
	{
		*(command->cmd) = token->str;
		command->cmd++;
		token = token->next;
		if (!token)
			break ;
	}
	*(command->cmd) = NULL;
	command->cmd -= i;
	i = count_redirs(token);
	if (!i)
	{
		command->redir = malloc(sizeof(char *));
		*(command->redir) = NULL;
		return (command);
	}
	else
		command->redir = malloc((sizeof(char *) * (i + 1)));
	// while (token_type_redir(token))
	while (token->type != PIPE)
	{
		*(command->redir) = token->str;
		command->redir++;
		token = token->next;
		if (!token)
			break ;
	}
	*(command->redir) = NULL;
	command->redir -= i;
	return (command);
}

void print_commands(t_command *command)
{
	int i = 0;
	if (!command)
	{
		return ;
	}
	while(*(command->cmd))
	{
		printf("%s\n", *(command->cmd));
		command->cmd++;
	}
		printf("not here\n");
	while(*(command->redir))
	{
		printf("%s\n", *(command->redir));
		command->redir++;
	}
}

int main(void)
{
	t_token *token;
	t_command *command;
	char *input;
	char *args[10] = {".", NULL};

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
			// run_command(token->str, args);
			print_tokens(token);
			command = convert_tokens(token);
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
