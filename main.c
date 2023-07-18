/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ekinnune.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:10:42 by ekinnune          #+#    #+#             */
/*   Updated: 2023/07/18 14:07:45 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	int					i;
	struct sigaction	sa;
	t_command			*command;
	t_token				*token;

	i = argc;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_flags = SA_RESTART;
	token = NULL;
	command = NULL;
	if (argv[1] == NULL)
	{
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
	return (0);
}
