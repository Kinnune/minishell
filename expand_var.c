/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 11:03:22 by ekinnune          #+#    #+#             */
/*   Updated: 2023/07/05 11:04:29 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_varname(char c)
{
	// str[i + j] && (ft_isalnum(str[i + j]) || str[i + j] == '_' || str[i + j] == '\''
	return (c && (ft_isalnum(c) || c == '_' || c == '\''));
}

int check_dollar(char *str)
{
	if (!str)
		return (-1);
	if (!*str)
		return (0);
	if (*str == '$')
		return (1);
	return (check_dollar(str + 1));
}

int	expand_command_args(t_command *command)
{
	int i;

	i = 0;
	while (*(command->cmd + i))
	{
		check_var_logic((command->cmd + i));
		if (!(command->cmd + i))
			return (-1);
		i++;
	}
	// check_var_logic(&command->here_doc);
	// printf("we crash\n");
	return (0);
}

char	*expand_var(char *str)
{
	char *expanded;
	char *temp;
	int	var_len;
	int	str_len;
	int	i;
	int	j;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	j = 1;
	while (valid_varname(*(str + (i + j))))
		j++;
	temp = ft_strndup(str + i, j);
	if (!temp)
		return (NULL);
	str_len = ft_strlen(str) - j;
	i = 0;
	while (g_data.envir[i])
	{
		j = 0;
		while (g_data.envir[i][j] != '=' && g_data.envir[i][j])
			j++;
		if (!ft_strncmp(g_data.envir[i], temp + 1, j))
			break ;
		i++;
	}
	if (!g_data.envir[i])
		return (ft_calloc(1, 1));//we failed to find var return null or empty string??
	j = 0;
	while (g_data.envir[i][j] && g_data.envir[i][j] != '=')
		j++;
	if (g_data.envir[i][j])
		j++;
	else
		return (NULL);
	var_len = ft_strlen(&g_data.envir[i][j]);
	if (*str == '$' && ft_strlen(str) == var_len)
		return (ft_strdup(&g_data.envir[i][j]));
	if (g_data.envir[i][j] == '\'')
		var_len -= 2;
	expanded = ft_calloc(1, str_len + var_len + 1);
	if (!expanded)
		return (NULL);//handle error
	free (temp);
	temp = &g_data.envir[i][j];
	i = 0;
	j = 0;
	while (str[i] != '$' && str[i])
	{
		expanded[i] = str[i];
		i++;
	}
	str += i;
	if (*str)
		str++;
	while (valid_varname(*str))
		str++;
	ft_memcpy(expanded + i, temp + j, ft_strlen(temp + j));
	j = i + ft_strlen(temp + j);
	ft_memcpy(expanded + j, str, ft_strlen(str));
	return (expanded);
}

char *check_var_logic(char **str)
{
	char *temp;

	if (!str)
		return (NULL);
	if (!*str)
		return (NULL);
	if (!check_dollar(*str))
		return (*str);
	temp = expand_var(*str);
	free (*str);
	*str = temp;
	return (check_var_logic(str));
}