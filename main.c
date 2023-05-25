/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:18:04 by djames            #+#    #+#             */
/*   Updated: 2023/05/24 17:04:22 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//struct termios orig_termios;

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

int main(int argc, char **argv, char **envp)
{
	
	int i = argc;
	char *new;
	new = argv[1];
	char *prom_line;
	int pid;
	struct sigaction sa ;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_flags =SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaction(SIGINT, &sa, NULL);
	pid = getpid();
	copy_env(envp);
	//printEnvironment(envp);
	printf("este es el pid %d\n", pid);
	if(envp)
		i++;
	while(1)
	{
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
		i = check_built(prom_line);
		if(i == 256)
		{
			printf("exit\n");
			printf("MINISHELL: exit: a: numeric argument required\n");
			i = 255;
		}
		else if(i >= 0 && i <= 255)
			printf("exit\n");
		else if(i == 256)
		{
			printf("exit\n");
			printf("MINISHELL: exit: too many arguments\n");
			i = 255;
		}

		if(prom_line)
		{
			free(prom_line);
		}
		if(i != 257)
			exit(i);
	}
	return (i);
}