/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:43:50 by djames            #+#    #+#             */
/*   Updated: 2023/07/19 14:24:08 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_equal(int flag, char *str)
{
	int	i;
	int	equal;

	i = 0;
	equal = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			equal = 1;
		i++;
	}
	if (flag == 0 && equal == 0)
	{
		return (NULL);
	}
	return (str);
}

char	*check_temp(char *str, int flag, char *str2)
{
	int		i;
	char	*ret;

	i = 0;
	ret = str;
	if ((ft_isdigit(str[i]) || !(ft_isalpha(str[i]))))
	{
		if (str[i] != '_')
		{
			if (flag == 0)
				free(str);
			return (print_errorexport(str2, flag));
		}
	}
	while (str[++i] != '\0')
	{
		if (!(ft_isalnum(str[i]) || (str[i] == '_')))
		{
			if (flag == 0)
				free(str);
			return (print_errorexport(str2, flag));
		}
	}
	return (ret);
}

char	*find_equal_2(char *str)
{
	int		i;
	int		equal;
	char	*temp;

	i = 0;
	equal = 0;
	while (str[i] != '\0' && equal == 0)
	{
		if (str[i] == '=')
			equal = 1;
		i++;
	}
	temp = malloc((i + 1) * (sizeof(char)));
	if (!temp)
		exit(-1);
	if (equal == 1)
		i--;
	equal = 0;
	while (equal < i)
	{
		temp[equal] = str[equal];
		equal++;
	}
	temp[equal] = '\0';
	return (temp = check_temp(temp, 0, str));
}

void	print_environment(int flag)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	if (flag == 0)
	{
		while (g_data.envir[i] != NULL)
		{
			temp = find_equal(1, g_data.envir[i]);
			add_quotes(temp);
			i++;
		}
	}
	else if (flag == 1)
	{
		i = 0;
		while (g_data.envir[i] != NULL)
		{
			temp = find_equal(0, g_data.envir[i]);
			if (temp != NULL)
				printf("%s\n", temp);
			i++;
		}
	}
}

void	add_quotes(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	write(1, "declare -x ", 11);
	while (str[i] != '\0')
	{
		write(1, &(str[i]), 1);
		if (str[i] == '=')
		{
			write(1, "\"", 1);
			flag = 1;
		}
		i++;
	}
	if (flag == 1)
		write(1, "\"", 1);
	write(1, "\n", 1);
}
