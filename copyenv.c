/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copyenv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:01:51 by djames            #+#    #+#             */
/*   Updated: 2023/07/14 13:34:44 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_length_word(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		i++;
	}
	return (i);
}

void	copy_env(char **envp)
{
	int	lenght;
	int	i;

	i = 0;
	lenght = ft_length_word(envp);
	g_data.envir = malloc((lenght + 1) * (sizeof(char *)));
	g_data.envir[lenght] = NULL;
	while (i < lenght)
	{
		g_data.envir[i] = ft_strdup(envp[i]);
		i++;
	}
	if (g_data.flag1 == 0)
	{
		g_data.flag1 = 1;
		remove_string("OLDPWD");
		add_string("OLDPWD");
	}
}

void	aux_remove(void)
{
	int		lenght;
	int		i;
	char	**temp;

	i = 0;
	lenght = ft_length_word(g_data.envir);
	temp = malloc((lenght + 1) * (sizeof(char *)));
	temp[lenght] = NULL;
	while (i < (lenght))
	{
		temp[i] = ft_strdup(g_data.envir[i]);
		i++;
	}
	free_array(g_data.envir);
	copy_env(temp);
	free_array(temp);
}

void	ft_copy(int j)
{
	char	**temp;
	int		i;
	int		lenght;

	i = 0;
	lenght = ft_length_word(g_data.envir);
	temp = malloc((lenght) * (sizeof(char *)));
	temp[lenght - 1] = NULL;
	while (i < (lenght - 1))
	{
		if (i >= j)
		{
			temp[i] = ft_strdup(g_data.envir[i + 1]);
		}
		else
			temp[i] = ft_strdup(g_data.envir[i]);
		i++;
	}
	free_array(g_data.envir);
	copy_env(temp);
	free_array(temp);
}

int	remove_string(char *target_string)
{
	int		i;
	int		length;
	char	*remo;

	i = 0;
	length = ft_strlen(target_string);
	remo = (check_temp(target_string));
	if (remo == NULL)
		return (-1);
	while (g_data.envir[i] != NULL)
	{
		if (ft_strncmp(g_data.envir[i], target_string, length) == 0)
		{
			ft_copy(i);
			break ;
		}
		i++;
	}
	return (0);
}
