/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ekinnune.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:10:42 by ekinnune          #+#    #+#             */
/*   Updated: 2023/07/05 16:56:37 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//check for unitialized values


void disableRawMode() {
	//struct termios    term;
  	tcgetattr(STDIN_FILENO, &(g_data.term));
	g_data.term.c_lflag |= ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSANOW, &(g_data.term));
}

void enableRawMode() {
	//struct termios    term;
  tcgetattr(STDIN_FILENO, &(g_data.term));
  struct termios raw = g_data.term;
  raw.c_lflag &= ~(ECHOCTL);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void	handle_signal(int signal)
{
	//enableRawMode();
	if(signal == SIGINT)
	{
		ioctl(STDOUT_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
	}
}
void	handle_signal2(int signal)
{
	//disableRawMode();
	if(signal == SIGINT)
		write(1, "\n", 1);
}

int main(int argc, char **argv, char **envp)
{
	t_token *token;
	t_command *command;
	//char *input;
	int i = argc;
	char *new;
	new = argv[1];
	char *prom_line;
	//int pid;
	struct sigaction sa ;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_flags =SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaction(SIGINT, &sa, NULL);
	//pid = getpid();
	copy_env(envp);
	//printf("este es el pid %d\n", pid);
	if(envp)
		i++;
	while (1)
	{
		command = NULL;
		token = NULL;
		//input = readline(">"); // prom so here I will make the split
		enableRawMode();
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
		// i = check_built(prom_line);// it is need to check in the pipe 
		// if(i == 256)
		// {
		// 	printf("exit\n");//writeestandar erro print dprintf not allow 
		// 	printf("MINISHELL: exit: a: numeric argument required\n");
		// 	i = 255;
		// }
		// else if(i >= 0 && i <= 255)
		// 	printf("exit\n");
		// else if(i == 256)
		// {
		// 	printf("exit\n");
		// 	printf("MINISHELL: exit: too many arguments\n");
		// 	i = 255;
		// }
		i=257;
		if(i == argc || i == 257)
	{
		
		if (!count_quotes(prom_line)) // cahnce to prom_line
			token = tokenizer(prom_line);
		if (!check_tokens(token))
		{
			// print_tokens(token);
			command = convert_tokens(token);
			i =check_list(command);
			if(i == 258)
			{
				printf("nyt on toimi \n");
				i = check_built(prom_line);// it is need to check in the pipe 
				if(i == 256)
				{
					printf("exit\n");//writeestandar erro print dprintf not allow 
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
			}
			// build_pipes(command);
			//handle_commands(command);
			//print_commands(command);// this we will not need
			// free_tokens(token);
			// printf("freed tokens\n");
			token = NULL;
		}
		// free_commands(command);
		// printf("freed commands\n");
        // execve(get_path(*command->cmd),command->cmd, g_data.envir);
		//if (input)
		//	free(input);
	}
		if(prom_line)
		{
			free(prom_line);
		}
		// if(i != 257)
		// 	exit(i);
	
	
	}
	//printf("%d", i);
	disableRawMode();
	return (i);
	//return (0);
}

// void	build_pipes(t_command *command)
// {
// 	if (!command)
// 		return ;
// 	// handle_pipes(command);
// 	build_pipes(command->next);
// }

// void	build_redirections(t_command *command)
// {
// 	if (!command)
// 		return ;
// 	if (!*(command->redir))
// 		return ;
// 	handle_redirections(command);
// 	// if (command->next)
// 	// 	build_redirecitons(command->next);
// }

// // command->next
// // *command->redir;
// // execve(get_path(*command->cmd), (command->cmd + 1), g_data.envir);

// void	handle_commands(t_command *command)
// {
// 	pid_t pid;

// 	if (!command)
// 		return ;
// 	pid = fork();
// 	if (pid < 0)
// 		return ;
// 	if (pid == 0)
// 	{
// 		build_redirections(command);
// 		// run_command(command);
// 	}
// 	else
// 		handle_commands(command->next);
// }
