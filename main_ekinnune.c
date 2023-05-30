/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ekinnune.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:10:42 by ekinnune          #+#    #+#             */
/*   Updated: 2023/05/29 17:57:40 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	t_token *token;
	char *input;
	char *args[10] = {".", NULL};

	// print_environ();
	// run_command("ls", args);
	// printf("keeps going\n");
	// return (0);
	while (1)	
	{
		input = readline(">");
		// printf("[%s]\n", input);
		// list = build_commands(input);
		token = tokenizer(input);
		if (token)
		{
			run_command(token->str, args);
			print_tokens(token);
			free_tokens(token);
		}
		// printf("[%d]\n", lst_size(list));
		// lst_print_args(list);
		// lst_free(list);
		if (input)
			free(input);
	}
	return (0);
}
