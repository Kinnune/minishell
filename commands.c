/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:29:25 by ekinnune          #+#    #+#             */
/*   Updated: 2023/06/21 15:55:14 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int token_type_command(t_token *token)
{
	if (!token)
		return (0);
	return (token->type == NAME |
				token->type == DQUOTE |
				token->type == SQUOTE |
				token->type == ENVAR |
				token->type == EXVAR);
}

int token_type_redir(t_token *token)
{
	if (!token)
		return (0);
	return (token->type == RDIRIN |
				token->type == RDIROUT |
				token->type == RDIRAPP |
				token->type == RDIRDEL);
}

t_token *skip_i_token(t_token *token, int i)
{
	if (token && i > 0)
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
	else if (token_type_redir(token) && token->next)
	{
		return (count_name(token->next->next));
	}
	return (0);
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
				return (2 + count_redir(find_redir(token->next->next)));
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
			return (2 + set_redir(command, find_redir(token->next->next)));
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
	else if (token_type_redir(token) && token->next)
		return (set_name(command, token->next->next));
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
	command->redir = ft_calloc(i + 1, sizeof(char *));
	if (!command->redir)
		;//handle malloc error
	i = set_redir(command, test_token);
	command->redir -= i;
	i = count_name(token);
	command->cmd = ft_calloc(i + 1, sizeof(char *));
	if (!command->cmd)
		;//handle malloc error
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
