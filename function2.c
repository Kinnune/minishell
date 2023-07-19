/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:49:16 by djames            #+#    #+#             */
/*   Updated: 2023/07/19 14:10:33 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_built2(char **str)
{
	int	i;

	i = 1;
	if (str[0] != NULL && ft_strncmp(str[0], "pwd\0", 4) == 0)
	{
		ft_pwd();
		i = 0;
	}
	else if (str[0] != NULL && ft_strncmp(str[0], "export\0", 7) == 0)
	{
		export_start(str);
		i = 0;
	}
	else if (str[0] != NULL && ft_strncmp(str[0], "unset\0", 7) == 0)
	{
		if (str[1] != NULL)
			remove_start(str);
		i = 0;
	}
	else if (str[0] != NULL && ft_strncmp(str[0], "env\0", 4) == 0)
	{
		start_env(str);
		i = 0;
	}
	return (i);
}

char	*find_helper(int equal, int j, int i)
{
	char	*str2;

	equal = ft_strlen(g_data.envir[i]) - 4;
	str2 = malloc(sizeof(char) * (equal + 1));
	if (!str2)
		return (NULL);
	equal = 0;
	while (g_data.envir[i][j] != '\0')
	{
		str2[equal] = g_data.envir[i][j];
		j++;
		equal++;
	}
	str2[equal] = '\0';
	return (str2);
}

void	add_string(char *new_string)
{
	int		lenght;
	int		i;
	char	*remo;
	char	**temp;

	i = 0;
	remo = (find_equal_2(new_string));
	if (remo == NULL)
		return ;
	if ((find_word(new_string)) == 1)
	{
		free(remo);
		return ;
	}
	remove_string(remo);
	lenght = ft_length_word(g_data.envir);
	temp = malloc((lenght + 2) * (sizeof(char *)));
	if (!temp)
		exit(-1);
	temp[lenght + 1] = NULL;
	aux_add25(&i, lenght, temp);
	temp[i] = ft_strdup(new_string);
	if (!temp[i])
		exit(-1);
	ft_free_copy(temp, remo);
}

int	find_25(char *str)
{
	int	i;
	int	equal;

	i = 0;
	equal = 0;
	while (str[i] != '\0' && equal == 0)
	{
		if (str[i] == '=')
			equal = 1;
		i++;
	}
	return (equal);
}

int	find_word(char *str)
{
	int	i;
	int	equal;
	int	length;

	i = 0;
	equal = find_25(str);
	length = ft_strlen(str);
	while (g_data.envir[i] != NULL)
	{
		if (ft_strncmp(g_data.envir[i], str, length) == 0)
		{
			if (equal == 1)
			{
				ft_copy(i);
				return (0);
			}
			return (1);
		}
		i++;
	}
	return (0);
}
