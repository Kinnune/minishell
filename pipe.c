/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 12:48:45 by djames            #+#    #+#             */
/*   Updated: 2023/07/14 14:54:14 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execaux(int i, pid_t *pid, int **fd)
{
	int	j;
	int	madona;

	j = 0;
	madona = -1;
	close_pipe(fd, i);
	while (j <= i)
	{
		waitpid(pid[j], &madona, 0);
		j++;
	}
	g_data.flag = WEXITSTATUS(madona);
	if (WIFSIGNALED(madona))
	{
		if (WTERMSIG(madona) == SIGQUIT)
			write(STDERR_FILENO, "Quit: 3\n", 8);
		else if (WTERMSIG(madona) == SIGSEGV)
			write(STDERR_FILENO, "Segmentation fault: 11\n", 23);
	}
	ft_free(fd, pid, i);
	return (madona);
}

void	ft_exec35(t_command *command, int i, int **fd, int j)
{
	int	madona;

	madona = 258;
	disable_rawmode();
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!check_redirect_in(command->redir, command->here_doc) && j != 0)
		dup2(fd[j - 1][0], STDIN_FILENO);
	if (!check_redirect_out(command->redir) && j <= (i - 1))
		dup2(fd[j][1], STDOUT_FILENO);
	close_pipe(fd, j);
	madona = check_built(command->cmd);
	if (madona != 1)
		exit(madona);
	else if (execve(get_path(*command->cmd), command->cmd, g_data.envir) != 0)
	{
		dprintf(2, "exiting cause of error\n");
		exit(-1);
	}
}
