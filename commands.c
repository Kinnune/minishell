/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:29:25 by ekinnune          #+#    #+#             */
/*   Updated: 2023/07/18 12:27:57 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*convert_tokens(t_token *token)
{
	int			i;
	t_command	*command;
	t_token		*test_token;

	if (!token)
		return (NULL);
	command = ft_calloc(1, sizeof(t_command));
	if (!command)
		exit(-1);
	test_token = find_redir(token);
	i = count_redir(test_token);
	command->redir = ft_calloc(i + 1, sizeof(char *));
	if (!command->redir)
		exit(-1);
	i = set_redir(command, test_token);
	command->redir -= i;
	i = count_name(token);
	command->cmd = ft_calloc(i + 1, sizeof(char *));
	if (!command->cmd)
		exit(-1);
	i = set_name(command, token);
	command->cmd -= i;
	command->next = convert_tokens(skip_pipe(token));
	return (command);
}

int	set_redir(t_command *command, t_token *token)
{
	g_data.flag2 = 0;
	if (!token)
		return (0);
	if (token_type_redir(token))
	{
		if (token->next)
		{
			*(command->redir) = ft_strdup(token->str);
			if (!*(command->redir))
				exit(-1);
			*(command->redir + 1) = ft_strdup(token->next->str);
			if (!*(command->redir + 1))
				exit(-1);
			if (token->type == RDIRDOC)
			{
				if (command->here_doc)
					free(command->here_doc);
				command->here_doc = here_doc(token->next->str);
			}
			command->redir += 2;
			return (2 + set_redir(command, find_redir(token->next->next)));
		}
	}
	return (0);
}

int	set_name(t_command *command, t_token *token)
{
	if (!token)
		return (0);
	if (token_type_command(token))
	{
		*(command->cmd) = ft_strdup(token->str);
		if (!*(command->cmd))
			exit(-1);
		command->cmd += 1;
		return (1 + set_name(command, token->next));
	}
	else if (token_type_redir(token) && token->next)
		return (set_name(command, token->next->next));
	return (0);
}

t_token	*find_redir(t_token *token)
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
