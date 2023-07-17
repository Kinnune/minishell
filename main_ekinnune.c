/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ekinnune.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:10:42 by ekinnune          #+#    #+#             */
/*   Updated: 2023/07/17 14:40:08 by ekinnune         ###   ########.fr       */
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
	check_redirect_in(command->redir, command->here_doc);
	check_redirect_out(command->redir);
	ret_val = check_built(command->cmd);
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
		if (!command->next)
			i = local_builtin(command);
		if (i)
			check_list(command);
		free_tokens(token);
		free_commands(command);
		token = NULL;
	}
	return (i);
}

int	main(int argc, char **argv, char **envp)
{
	int					i;
	struct sigaction	sa;
	t_command			*command;
	t_token				*token;

	i = argc;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	g_data.flag = 0;
	g_data.flag1 = 0;
	sigaction(SIGINT, &sa, NULL);
	copy_env(envp);
	while (1)
		i = start_main(token, command);
	return (i);
}
