/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:44:35 by djames            #+#    #+#             */
/*   Updated: 2023/07/14 12:49:16 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **tem)
{
	int	i;

	i = 0;
	while (tem[i] != NULL)
	{
		free(tem[i]);
		i++;
	}
	free(tem);
}

int	chance_oldpwd(int i, char *str)
{
	char	**tem;
	char	*str3;
	char	*str2;

	tem = ft_split(g_data.envir[i], '=');
	str3 = ((ft_strjoin("OLDPWD=", tem[1])));
	add_string(str3);
	str2 = ((ft_strjoin("PWD=", str)));
	add_string(str2);
	free(str3);
	free(str2);
	free_split(tem);
	return (0);
}

int	chance_pwd(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (g_data.envir[i] != NULL)
	{
		if (ft_strncmp(g_data.envir[i], "PWD", 3) == 0 && flag == 0)
		{
			chance_oldpwd(i, str);
			flag = 1;
		}
		i++;
	}
	return (0);
}

char	*find_word2(char *str)
{
	int	i;
	int	j;
	int	equal;
	int	length;

	j = 0;
	equal = 0;
	length = ft_strlen(str);
	i = 0;
	while (g_data.envir[i] != NULL)
	{
		if (ft_strncmp(g_data.envir[i], str, length) == 0)
		{
			while (g_data.envir[i][j] != '\0' && equal == 0)
			{
				if (g_data.envir[i][j] == '=')
					equal = 1;
				j++;
			}
			return (find_helper(equal, j, i));
		}
		i++;
	}
	return (NULL);
}

int	change_directory(char *path)
{
	char	*result;
	char	buf[BUFFER];
	char	**path1;

	if (path == NULL)
		path = find_word2("HOME");
	if (chdir(path) == 0)
	{
		result = getcwd(buf, sizeof(buf));
		if (!(result != NULL))
		{
			perror("MINISHELL");
			return (1);
		}
	}
	else
	{
		perror("MINISHELL");
		return (1);
	}
	chance_pwd(buf);
	return (0);
}
