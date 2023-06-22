/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ekinnune.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:10:42 by ekinnune          #+#    #+#             */
/*   Updated: 2023/06/22 12:50:49 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int main(void)
{
	t_token *token;
	t_command *command;
	char *input;

	while (1)
	{
		input = readline(">");
		if (!count_quotes(input))
			token = tokenizer(input);
		printf("'%s'\n", get_path(token->str));
		if (token && !check_tokens(token))
		{
			// print_tokens(token);
			command = convert_tokens(token);
			// build_pipes(command);
			//handle_commands(command);
			print_commands(command);
			token = NULL;
		}
		free_tokens(token);
		//free_commands(command);
		if (input)
			free(input);
	}
	return (0);
}
