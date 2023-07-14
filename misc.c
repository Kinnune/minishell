/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 12:08:01 by ekinnune          #+#    #+#             */
/*   Updated: 2023/07/14 12:21:31 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_error(void)
{
	write(2, "minishell: syntax error\n", 24);
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
	else if (*input == '$')
		return (is_var(input));
	else
		return (NULL);
}

int	special_symbol(char input)
{
	return (input == '>' | input == '<' | input == '$'
		| input == '|' | input == '\'' | input == '"'
		| input == ' ' | input == '\t' | input == '\0');
}


void	free_2d(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (*(array + i))
	{
		free(*(array + i));
		i++;
	}
	free(array);
}

void	free_commands(t_command *command)
{
	if (!command)
		return ;
	free_commands(command->next);
	if (command->redir)
		free_2d(command->redir);
	if (command->cmd)
		free_2d(command->cmd);
	if (command->here_doc)
		free(command->here_doc);
	free(command);
}
