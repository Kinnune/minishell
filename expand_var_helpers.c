/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:54:31 by ekinnune          #+#    #+#             */
/*   Updated: 2023/07/14 16:59:20 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_exvar(int *i, char **buff)
{
	char	*temp;
	char	*temp_buff;

	temp = ft_itoa(g_data.flag);
	if (!temp)
		exit(-1);
	temp_buff = ft_strjoin(*buff, temp);
	if (!temp_buff)
		exit(-1);
	free(*buff);
	free(temp);
	*buff = temp_buff;
	*i += 2;
}

void	handle_varname(int *i, char **buff, char *str)
{
	char	*temp;
	char	*temp_buff;

	temp = set_varname(str + (*i));
	if (*(temp) != '$')
		get_varname(&temp);
	temp_buff = ft_strjoin(*buff, temp);
	if (!temp_buff)
		exit (-1);
	free(*buff);
	*buff = temp_buff;
	if (temp)
		free(temp);
	(*i)++;
	while (valid_varname(*(str + (*i))))
		(*i)++;
}

void	handle_blank(int *i, char **buff, char *str)
{
	char	*temp;
	char	*temp_buff;

	temp = ft_strchr(str + (*i), '$');
	if (!temp)
		temp = ft_strchr(str + (*i), '\0');
	temp_buff = ft_strndup(str + (*i), (int)(temp - (str + (*i))));
	if (!temp_buff)
		exit(-1);
	(*i) += (int)(temp - (str + (*i)));
	temp = ft_strjoin(*buff, temp_buff);
	if (!temp)
		exit(-1);
	free(*buff);
	*buff = temp;
	free(temp_buff);
}

char	*check_var_logic(char **str)
{
	char	*temp;

	if (!str)
		return (NULL);
	if (!*str)
		return (NULL);
	if (**str == '\'' && *((*str) + ft_strlen(*str) - 1) == '\'')
		return (*str);
	temp = expand_var(*str);
	free (*str);
	*str = temp;
	return (*str);
}

int	valid_varname(char c)
{
	return (c && (ft_isalnum(c) || c == '_' || c == '\''));
}
