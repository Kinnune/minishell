/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:08:08 by ekinnune          #+#    #+#             */
/*   Updated: 2023/07/18 14:08:17 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	enable_rawmode(void)
{
	struct termios	raw;

	tcgetattr(STDIN_FILENO, &(g_data.term));
	raw = g_data.term;
	raw.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void	handle_signal(int signal)
{
	enable_rawmode();
	if (signal == SIGINT)
	{
		ioctl(STDOUT_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
	}
	g_data.flag2 = 1;
}

int	local_builtin(t_command *command)
{
	int	std_fd[3];
	int	ret_val;

	ret_val = 1;
	if (*command->redir)
	{
		std_fd[0] = dup(STDIN_FILENO);
		std_fd[1] = dup(STDOUT_FILENO);
		std_fd[2] = dup(STDERR_FILENO);
	}
	ret_val = check_redirect_in(command->redir, command->here_doc);
	if (ret_val >= 0)
		ret_val = check_redirect_out(command->redir);
	if (ret_val >= 0)
		ret_val = check_built(command->cmd, 0);
	if (*command->redir)
	{
		dup2(std_fd[0], STDIN_FILENO);
		dup2(std_fd[1], STDOUT_FILENO);
		dup2(std_fd[2], STDERR_FILENO);
		close(std_fd[0]);
		close(std_fd[1]);
		close(std_fd[2]);
	}
	return (ret_val);
}

int	check_built3(t_token *token, t_command *command)
{
	int	i;

	i = 1;
	if (!check_tokens(token))
	{
		command = convert_tokens(token);
		expand_command_args(command);
		if (!command->next && is_builtin(*command->cmd))
			i = local_builtin(command);
		else
			check_list(command);
		free_tokens(token);
		free_commands(command);
		token = NULL;
	}
	return (i);
}

int	is_builtin(char *command)
{
	if (!command)
		return (0);
	return (!ft_strncmp(command, "echo", 5)
		|| !ft_strncmp(command, "cd", 3)
		|| !ft_strncmp(command, "pwd", 4)
		|| !ft_strncmp(command, "export", 7)
		|| !ft_strncmp(command, "unset", 6)
		|| !ft_strncmp(command, "env", 4)
		|| !ft_strncmp(command, "exit", 5));
}
