/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ekinnune.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:10:42 by ekinnune          #+#    #+#             */
/*   Updated: 2023/06/21 15:42:17 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (token && !check_tokens(token))
		{
			// print_tokens(token);
			command = convert_tokens(token);
			//handle_commands()
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
