/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 11:31:00 by ekinnune          #+#    #+#             */
/*   Updated: 2023/06/22 14:43:59 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_environ(void)
{
	extern char	**environ;
	char		*buf;
	for (int i = 0; *(environ + i); i++)
	{
		printf("%s, %d\n", *(environ + i), i);
	}
	buf = getwd(NULL);
	printf("%s\n", buf);
}

//to-do
//actually setting getting the path
//correct error messages depending on path type
//checking of execution right

void	command_errors(char *path, char *msg)
{
	if (path && msg)
		printf("minishell: %s: %s\n", path, msg);
	else if (msg)
		printf("minishell: %s\n", msg);
}

int count_dot_dot(char *str)
{
	int i;

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
	int i;
	char *test;


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
			{
				i++;
			}
			ft_memmove(test - i, test + 3, ft_strlen(test + 3) + 1);
		}
		// else
		// 	ft_memmove(test, test + 3, ft_strlen(test + 2) + 1);
		return (dot_slash_remove(path));
	}
	return (path);
}

char *get_path(char *command)
{
	extern char	**environ;
	char **path_split;
	char path[PATH_MAX * 2];
	char *path_ptr;
	char *temp_ptr;
	char *error_msg;
	int i;

	if (!command)
		return (NULL);
	if (*command != '/')
	{
		path_ptr = &path[0];
		*path_ptr = 0;
		if (ft_strchr(command, '/')) //relative path
		{
			getcwd(path_ptr, PATH_MAX);
			ft_memcpy(path_ptr + ft_strlen(path_ptr), "/", 2);
			ft_memcpy(path_ptr + ft_strlen(path_ptr), command, ft_strlen(command) + 1);
		}
		else //this command needs to be found matched to environ [13]
		{
			// this environ index was 13 before and apparently working???
			// if it changed that is scary
			path_split = ft_split((*(environ + 11) + 5), ':');
			if (!path_split)
				return (NULL);
			i = 0;
			while (*(path_split + i))
			{
				ft_memcpy(path_ptr, *(path_split + i), ft_strlen(*(path_split + i)) + 1);
				ft_memcpy(path_ptr + ft_strlen(path_ptr), "/", 2);
				ft_memcpy(path_ptr + ft_strlen(path_ptr), command, ft_strlen(command) + 1);
				if (!access(path_ptr, F_OK))
					break ;
				i++;
			}
			if (!*(path_split + i))
				path_ptr = NULL;
			i = 0;
			while (*(path_split + i))
			{
				free(*(path_split + i));
				i++;
			}
			free(path_split);
		}
	}
	else //absolute path
	{
		path_ptr = command;
	}
	path_split = NULL;
	dot_slash_remove(path_ptr);
	return (path_ptr);
}

	// if (!access(path_ptr, F_OK))
	// {
	// 	if (access(path_ptr, X_OK))
	// 		command_errors(path_ptr, "Permission denied");
	// }
	// else
	// 	command_errors(path_ptr, "No such file or directory");
		//not sure if its ok to trust environ or should use getcwd
		// ft_memcpy(path_ptr, (*(environ + 8)) + 4, ft_strlen((*(environ + 8)) + 4) + 1);
		// temp_ptr = ft_strjoin(path_ptr, command);
		// printf("[%s]\n", path_ptr);
			// ../ can be mixed in the middle of stuff so properly build the path
			// and none of this bs that happens here that relies on it being in the start
			// dot_slash_remove(, command);
