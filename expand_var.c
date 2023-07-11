/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 11:03:22 by ekinnune          #+#    #+#             */
/*   Updated: 2023/07/11 19:20:37 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_varname(char c)
{
	// str[i + j] && (ft_isalnum(str[i + j]) || str[i + j] == '_' || str[i + j] == '\''
	return (c && c != '/' && (ft_isalnum(c) || c == '_' || c == '\''));
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

void	remove_quotes(char **str2d)
{
	char *str = *str2d;
	char quote;

	if (!*str && ft_strlen(str) < 2)
		return ;
	quote = *str;
	if (quote != '\'' && quote != '"')
		return  ;
	if (*(str + (ft_strlen(str) - 1)) == quote)
	ft_memmove(str, str + 1, ft_strlen(str + 1));
	*(str + (ft_strlen(str) - 2)) = '\0';
}

int	expand_command_args(t_command *command)
{
	int i;

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
		if (!i % 2)
			check_var_logic((command->redir + i));
			remove_quotes((command->redir + i));
			if (!(command->redir + i))
				return (-1);
		i++;
	}
	check_var_logic(&command->here_doc);
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
	if (str[i] && str[i + 1] == '?')
	{
		temp = ft_itoa(g_data.flag);
		expanded = ft_calloc(ft_strlen(str) - 2 + ft_strlen(temp) + 1, sizeof(char));
		ft_memcpy(expanded, str, i);
		ft_memcpy(expanded + ft_strlen(expanded), temp, ft_strlen(temp));
		ft_memcpy(expanded + ft_strlen(expanded), str + i + 2, ft_strlen(str + i + 2));
		free(temp);
		return (expanded);
	}		
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
	if (**str == '\'' && *((*str) + ft_strlen(*str) - 1) == '\'')
		return (*str);
	if (!check_dollar(*str))
		return (*str);
	temp = expand_var(*str);
	free (*str);
	*str = temp;
	return (check_var_logic(str));
}
