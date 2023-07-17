/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:13:24 by djames            #+#    #+#             */
/*   Updated: 2023/07/17 16:38:59 by djames           ###   ########.fr       */
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
