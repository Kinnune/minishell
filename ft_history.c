/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:13:24 by djames            #+#    #+#             */
/*   Updated: 2023/07/18 17:08:50 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_history(char *prom)
{
	if (prom != NULL && (ft_strlen(prom) > 0))
		add_history(prom);
}

void	print_errorexport(char *str, int flag)
{
	int	i;

	i = ft_strlen(str);
	if (flag == 0)
		write(STDERR_FILENO, "MINISHELL: export: `", 20);
	else if (flag == 1)
		write(STDERR_FILENO, "MINISHELL: unset: `", 19);
	write(STDERR_FILENO, str, i);
	write(STDERR_FILENO, "': not a valid identifier\n", 26);
}

void	match_aux(int path_i, char **path_split, char *path_ptr, char *command)
{
	ft_memcpy(path_ptr, *(path_split + path_i), ft_strlen(*(path_split
				+ path_i)) + 1);
	ft_memcpy(path_ptr + ft_strlen(path_ptr), "/", 2);
	ft_memcpy(path_ptr + ft_strlen(path_ptr),
		command, ft_strlen(command) + 1);
}

void	start_env(char **str)
{
	int	i;

	i = 0;
	if (str[1] == NULL)
		print_environment(1);
	else
	{
		i = ft_strlen(str[1]);
		write(STDERR_FILENO, "env: ", 5);
		write(STDERR_FILENO, str[1], i);
		write(STDERR_FILENO, ": No such file or directory\n", 28);
	}
}
