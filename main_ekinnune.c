/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ekinnune.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:10:42 by ekinnune          #+#    #+#             */
/*   Updated: 2023/07/05 11:05:47 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_token *token;
	t_command *command;
	char *input;

	copy_env(envp);
	while (1)
	{
		command = NULL;
		token = NULL;
		input = readline(">");
		if (!count_quotes(input))
			token = tokenizer(input);
		if (!check_tokens(token))
		{
			// print_tokens(token);
			command = convert_tokens(token);
			expand_command_args(command);
			print_commands(command);
			check_list(command);
			// build_pipes(command);
			//handle_commands(command);
			// free_tokens(token);
			// printf("freed tokens\n");
			token = NULL;
		}
		// free_commands(command);
		// printf("freed commands\n");
        // execve(get_path(*command->cmd),command->cmd, g_data.envir);
		if (input)
			free(input);
	}
	return (0);
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
