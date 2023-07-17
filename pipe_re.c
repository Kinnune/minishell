/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_re.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 16:59:39 by djames            #+#    #+#             */
/*   Updated: 2023/07/17 16:49:26 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	close_pipe(int **fd, int i)
{
	int	j;

	j = 0;
	while (j <= i)
	{
		close(fd[j][0]);
		close(fd[j][1]);
		j++;
	}
	return (0);
}

int	ft_free(int **fd, int *pid, int i)
{
	int	j;

	j = 0;
	while (j <= i)
	{
		if (fd[j])
			free(fd[j]);
		j++;
	}
	free(fd);
	free(pid);
	return (0);
}

int	piepe_function(t_command *list, int i)
{
	int		**fd;
	pid_t	*pid;
	int		j;

	fd = malloc(sizeof(int *) * (i + 1));
	pid = malloc(sizeof(pid_t) * (i + 1));
	j = 0;
	while (j <= i)
	{
		fd[j] = malloc(sizeof(int) * 2);
		j++;
	}
	j = ft_exec(list, i, fd, pid);
	return (j);
}

int	ft_exec(t_command *command, int i, int **fd, pid_t *pid)
{
	int		j;
	int		madona;

	j = 0;
	madona = 258;
	while (j <= i)
	{
		if (pipe(fd[j]) == -1)
			ft_free(fd, pid, i);
		pid[j] = fork();
		if (pid[j] == -1)
			ft_free(fd, pid, i);
		if (pid[j] == 0)
		{
			ft_exec35(command, i, fd, j);
		}
		if (command->next)
			command = command->next;
		j++;
	}
	return (ft_execaux(i, pid, fd));
}

int	check_list(t_command *list)
{
	int			i;
	int			j;
	t_command	*temp;

	i = 0;
	temp = list;
	j = 0;
	while (temp != NULL)
	{
		temp = temp->next;
		i++;
	}
	j = piepe_function(list, i - 1);
	return (j);
}
