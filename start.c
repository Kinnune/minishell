/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:38:41 by djames            #+#    #+#             */
/*   Updated: 2023/07/17 14:39:22 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_start3(char *prom_line)
{
	if (prom_line == NULL)
	{
		printf("\033[1A");
		printf("\033[11C");
		printf("exit\n");
		if (prom_line)
			free(prom_line);
		exit(0);
	}
	ft_history(prom_line);
}

void	disable_rawmode(void)
{
	tcgetattr(STDIN_FILENO, &(g_data.term));
	g_data.term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &(g_data.term));
}

int	start_main(t_token *token, t_command *command)
{
	int		i;
	char	*prom_line;

	i = 1;
	command = NULL;
	token = NULL;
	g_data.flag2 = 0;
	enable_rawmode();
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_signal);
	prom_line = readline("MINISHELL$ ");
	ft_start3(prom_line);
	if (g_data.flag2 != 1)
	{	
		if (!count_quotes(prom_line))
			token = tokenizer(prom_line);
		i = check_built3(token, command);
	}
	if (prom_line)
		free(prom_line);
	return (i);
}
