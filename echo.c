/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:10:27 by djames            #+#    #+#             */
/*   Updated: 2023/07/17 14:12:45 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char **str, int newline)
{
	int	i;
	int	j;

	i = 1;
	if (newline == 0)
	{
		i = 2;
	}
	j = i;
	while (str[i] != NULL)
	{
		if (i == j)
			printf("%s", str[i]);
		else
			printf(" %s", str[i]);
		i++;
	}
	if (newline)
		printf("\n");
}

void	start_echo(char **str)
{
	int	i;

	i = 1;
	if (str[1] != NULL)
	{
		if (str[1][0] == '-' && str[1][1] == 'n' && str[1][2] == '\0')
			i = 0;
		echo(str, i);
	}
}

void	free_array(char **temp)
{
	int	i;

	i = 0;
	if (temp == NULL)
		return ;
	while (temp[i] != NULL)
	{
		free(temp[i]);
		i++;
	}
	free(temp);
}
