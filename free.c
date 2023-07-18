/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:32:40 by ekinnune          #+#    #+#             */
/*   Updated: 2023/07/18 12:27:21 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_2d(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (*(array + i))
	{
		free(*(array + i));
		i++;
	}
	free(array);
}

void	free_commands(t_command *command)
{
	if (!command)
		return ;
	free_commands(command->next);
	if (command->redir)
		free_2d(command->redir);
	if (command->cmd)
		free_2d(command->cmd);
	if (command->here_doc)
		free(command->here_doc);
	free(command);
}
