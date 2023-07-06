/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ekinnune.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:10:42 by ekinnune          #+#    #+#             */
/*   Updated: 2023/07/06 11:18:36 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void disableRawMode() {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &(g_data.orig_termios));
}

void enableRawMode() {
  tcgetattr(STDIN_FILENO, &(g_data.orig_termios));
  struct termios raw = g_data.orig_termios;
  raw.c_lflag &= ~(ECHOCTL);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void	handle_signal(int signal)
{
	enableRawMode();
	if(signal == SIGINT)
	{
		ioctl(STDOUT_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
	}
}

//not sure if leaks fd's
int	local_builtin(t_command *command)
{
	int std_fd[3];
	int ret_val;

	ret_val = 1;
	if (*command->redir)
	{
		std_fd[0] = dup(STDIN_FILENO);
		std_fd[1] = dup(STDOUT_FILENO);
		std_fd[2] = dup(STDERR_FILENO);
	}
	check_redirect_in(command->redir, command->here_doc);
	check_redirect_out(command->redir);
	ret_val = check_built(*command->cmd);
	if (*command->redir)
	{
		dup2(std_fd[0], STDIN_FILENO);
		dup2(std_fd[1], STDOUT_FILENO);
		dup2(std_fd[2], STDERR_FILENO);
	}
	return (ret_val);
}

int main(int argc, char **argv, char **envp)
{
	t_token *token;
	t_command *command;
	int i = argc;
	char *new;
	new = argv[1];
	char *prom_line;
	struct sigaction sa ;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_flags =SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);

	sigaction(SIGINT, &sa, NULL);
	copy_env(envp);
	if(envp)
		i++;
	while (1)
	{
		i = 1;
		command = NULL;
		token = NULL;
		
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_signal);
		prom_line = readline("MINISHELL$ ");
		if(prom_line == NULL)
		{	
			printf("\033[1A");
			printf("\033[11C");
			printf("exit\n");
			if(prom_line)
				free(prom_line);
			exit(0);
		} 
		ft_history(prom_line);

		
		if (!count_quotes(prom_line))
			token = tokenizer(prom_line);
		if (!check_tokens(token))
		{
			command = convert_tokens(token);
			expand_command_args(command);
			if (!command->next)
				i = local_builtin(command);
			if (i)
				check_list(command);
			free_tokens(token);
			token = NULL;
		}
		free_commands(command);
		if(prom_line)
			free(prom_line);
	}
	return (i);
}
