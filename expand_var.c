/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 11:03:22 by ekinnune          #+#    #+#             */
/*   Updated: 2023/07/18 12:27:37 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_var(char *str)
{
	char	*buff;
	int		i;

	if (!str)
		return (str);
	buff = ft_calloc(1, 1);
	if (!buff)
		exit(-1);
	i = 0;
	while (*(str + i))
	{
		if (*(str + i) == '$' && *(str + i + 1) == '?')
			handle_exvar(&i, &buff);
		else if (*(str + i) == '$')
			handle_varname(&i, &buff, str);
		else
			handle_blank(&i, &buff, str);
	}
	return (buff);
}

int	expand_command_args(t_command *command)
{
	int	i;

	i = 0;
	while (*(command->cmd + i))
	{
		check_var_logic((command->cmd + i));
		remove_quotes((command->cmd + i));
		if (!(command->cmd + i))
			return (-1);
		i++;
	}
	i = 0;
	while (*(command->redir + i))
	{
		check_var_logic((command->redir + i));
		remove_quotes((command->redir + i));
		if (!(command->redir + i))
			return (-1);
		i++;
	}
	check_var_logic(&command->here_doc);
	return (0);
}

void	remove_quotes(char **str2d)
{
	char	*str;
	char	quote;

	str = *str2d;
	if (!*str && ft_strlen(str) < 2)
		return ;
	quote = *str;
	if (quote != '\'' && quote != '"')
		return ;
	if (*(str + (ft_strlen(str) - 1)) == quote)
		ft_memmove(str, str + 1, ft_strlen(str + 1));
	*(str + (ft_strlen(str) - 2)) = '\0';
}

char	*set_varname(char *str)
{
	int		i;
	char	*temp;

	i = 0;
	str++;
	while (valid_varname(*(str + i)))
		i++;
	if (!i)
		temp = ft_strdup("$");
	else
		temp = ft_strndup(str, i);
	if (!temp)
		exit (-1);
	return (temp);
}

void	get_varname(char **name)
{
	int	i;
	int	j;

	i = 0;
	while (g_data.envir[i])
	{
		j = 0;
		while (g_data.envir[i][j] != '=' && g_data.envir[i][j])
			j++;
		if (!ft_strncmp(g_data.envir[i], *name, ft_strlen(*name)))
			break ;
		i++;
	}
	j++;
	free(*name);
	if (!g_data.envir[i])
		*name = NULL;
	else
	{
		*name = ft_strdup(&g_data.envir[i][j]);
		if (!name)
			exit(-1);
	}
}
