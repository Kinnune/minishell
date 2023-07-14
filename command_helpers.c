/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 12:23:04 by ekinnune          #+#    #+#             */
/*   Updated: 2023/07/14 12:23:19 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_type_command(t_token *token)
{
	if (!token)
		return (0);
	return (token->type == NAME
		| token->type == DQUOTE
		| token->type == SQUOTE
		| token->type == ENVAR
		| token->type == EXVAR);
}

int	token_type_redir(t_token *token)
{
	if (!token)
		return (0);
	return (token->type == RDIRIN
		| token->type == RDIROUT
		| token->type == RDIRAPP
		| token->type == RDIRDOC);
}

t_token	*skip_i_token(t_token *token, int i)
{
	if (token && i > 0)
		return (skip_i_token(token->next, i - 1));
	return (token);
}

int	count_name(t_token *token)
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

int	count_redir(t_token *token)
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
