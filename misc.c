/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 12:08:01 by ekinnune          #+#    #+#             */
/*   Updated: 2023/07/18 13:57:07 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_error(void)
{
	write(2, "MINISHELL: syntax error\n", 24);
	return (-1);
}

int	count_quotes(char *input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (*input)
	{
		if (*input == '\'' && !(j % 2))
			i++;
		if (*input == '\"' && !(i % 2))
			j++;
		input++;
	}
	if (i % 2 + j % 2)
		return (syntax_error());
	return (0);
}

t_token	*handle_name_symbol(const char *input)
{
	return (is_progname(input));
}

t_token	*handle_special_symbol(const char *input)
{
	if (*input == '\'' || *input == '"')
		return (is_quote(input));
	else if (*input == '<' | *input == '>')
		return (is_redir(input));
	else if (*input == '|')
		return (is_pipe(input));
	else
		return (NULL);
}

int	special_symbol(char input)
{
	return (input == '>' | input == '<'
		| input == '|' | input == '\'' | input == '"'
		| input == ' ' | input == '\t' | input == '\0');
}
