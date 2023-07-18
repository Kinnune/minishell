/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:13:24 by djames            #+#    #+#             */
/*   Updated: 2023/07/18 12:27:15 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_history(char *prom)
{
	if (prom != NULL && (ft_strlen(prom) > 0))
		add_history(prom);
}

void	print_errorexport(char *str)
{
	int	i;

	i = ft_strlen(str);
	write(STDERR_FILENO, "MINISHELL: exit: ", 17);
	write(STDERR_FILENO, str, i);
	write(STDERR_FILENO, ": not avalid identefier\n", 24);
}

void	match_aux(int path_i, char **path_split, char *path_ptr, char *command)
{
	ft_memcpy(path_ptr, *(path_split + path_i), ft_strlen(*(path_split
				+ path_i)) + 1);
	ft_memcpy(path_ptr + ft_strlen(path_ptr), "/", 2);
	ft_memcpy(path_ptr + ft_strlen(path_ptr),
		command, ft_strlen(command) + 1);
}
