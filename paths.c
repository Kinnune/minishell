/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 11:31:00 by ekinnune          #+#    #+#             */
/*   Updated: 2023/07/18 12:26:30 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_dot_dot(char *str)
{
	int	i;

	i = 0;
	while (ft_strnstr(str, "../", 3))
	{
		str += 3;
		i++;
	}
	return (i);
}

char	*dot_slash_remove(char *path)
{
	int		i;
	char	*test;

	test = ft_strnstr(path, "/./", ft_strlen(path));
	if (test && !ft_strnstr(test, "/../", 4))
	{
		ft_memmove(test, test + 2, ft_strlen(test + 2) + 1);
		return (dot_slash_remove(path));
	}
	test = ft_strnstr(path, "/../", ft_strlen(path));
	if (test)
	{
		if (test == path)
			ft_memmove(test, test + 3, ft_strlen(test + 3) + 1);
		else
		{
			i = 1;
			while (test - i != path && *(test - i) != '/')
				i++;
			ft_memmove(test - i, test + 3, ft_strlen(test + 3) + 1);
		}
		return (dot_slash_remove(path));
	}
	return (path);
}

int	get_path_index(void)
{
	int	i;

	i = 0;
	while (g_data.envir[i])
	{
		if (!ft_strncmp(g_data.envir[i], "PATH=", 5))
			break ;
		i++;
	}
	return (i);
}

char	*match_command(char *command, char *path_ptr)
{
	char	**path_split;
	int		path_i;

	path_i = get_path_index();
	path_split = NULL;
	if (path_i < ft_length_word(g_data.envir))
	{
		path_split = ft_split((*(g_data.envir + path_i) + 5), ':');
		if (!path_split)
			return (NULL);
		path_i = 0;
		while (*(path_split + path_i))
		{
			match_aux(path_i, path_split, path_ptr, command);
			if (!access(path_ptr, F_OK))
				break ;
			path_i++;
		}
		if (!*(path_split + path_i))
			path_ptr = NULL;
		free_2d(path_split);
	}
	else
		path_ptr = NULL;
	return (dot_slash_remove(path_ptr));
}

char	*get_path(char *command)
{
	char	*path_ptr;

	if (!command)
		return (NULL);
	if (*command != '/')
	{
		path_ptr = ft_calloc(2, PATH_MAX);
		if (!path_ptr)
			return (NULL);
		if (ft_strchr(command, '/'))
		{
			getcwd(path_ptr, PATH_MAX);
			ft_memcpy(path_ptr + ft_strlen(path_ptr), "/", 2);
			ft_memcpy(path_ptr + ft_strlen(path_ptr),
				command, ft_strlen(command) + 1);
		}
		else
			return (match_command(command, path_ptr));
	}
	else
		path_ptr = command;
	dot_slash_remove(path_ptr);
	return (path_ptr);
}
