/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ekinnune.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:10:42 by ekinnune          #+#    #+#             */
/*   Updated: 2023/06/20 16:35:16 by ekinnune         ###   ########.fr       */
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
		here_doc(input);
		// token = tokenizer(input);

		// if (token)
		// {
		// 	print_tokens(token);
		// 	command = convert_tokens(token);
		// 	print_commands(command);
		// }
		if (input)
			free(input);
	}
	return (0);
}
