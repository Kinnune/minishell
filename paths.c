/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 11:31:00 by ekinnune          #+#    #+#             */
/*   Updated: 2023/05/24 16:33:25 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_environ(void)
{
	extern char	**environ;
	char		*buf;
	for (; *environ; environ++)
	{
		printf("%s\n", *environ);
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

int	run_command(char *command, char **args)
{
	extern char	**environ;
	char path[PATH_MAX];
	char *path_ptr;
	char *error_msg;
	int exec_ret;

	if (*command != '/')
	{
		path_ptr = &path[0];
		if (ft_strchr(command, '/'))
		{
			//this is a relative path
			;
		}
		else
		{
			//this command needs to be found
			;
		}
	}
	else
	{
		//this is an absolute path
		path_ptr = command;
	}
	exec_ret = execve(command, args, environ);
	if (!access(command, F_OK))
	{
		if (access(command, X_OK))
			command_errors(command, "Permission denied");
	}
	else
		command_errors(command, "No such file or directory");
	return (exec_ret);
}