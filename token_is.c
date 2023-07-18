/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_is.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 12:09:30 by ekinnune          #+#    #+#             */
/*   Updated: 2023/07/18 12:25:36 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*is_pipe(const char *input)
{
	return (make_token(input, 1, PIPE));
}

t_token	*is_var(const char *input)
{
	size_t	size;

	if (*(input + 1) == '?')
		return (make_token(input, 2, EXVAR));
	size = 0;
	while (*(input + size) != '=' && *(input + size) != ' ' && *(input + size))
		size++;
	return (make_token(input, size, ENVAR));
}

t_token	*is_quote(const char *input)
{
	enum e_type	token_type;
	size_t		size;

	if (*input == '\'')
		token_type = SQUOTE;
	else
		token_type = DQUOTE;
	size = 1;
	while (*(input + size) != *input)
	{
		if (!*(input + size))
			return (NULL);
		size++;
	}
	size++;
	return (make_token(input, size, token_type));
}

t_token	*is_progname(const char *input)
{
	size_t	size;

	size = 0;
	while (!special_symbol(*(input + size)))
		size++;
	return (make_token(input, size, NAME));
}

t_token	*is_redir(const char *input)
{
	if (*input == '<')
	{
		if (*(input + 1) == '<')
			return (make_token(input, 2, RDIRDOC));
		else
			return (make_token(input, 1, RDIRIN));
	}
	if (*input == '>')
	{
		if (*(input + 1) == '>')
			return (make_token(input, 2, RDIRAPP));
		else
			return (make_token(input, 1, RDIROUT));
	}
	return (NULL);
}
