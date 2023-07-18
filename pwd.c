/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:33:43 by djames            #+#    #+#             */
/*   Updated: 2023/07/18 12:26:08 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	buf[BUFFER];
	char	*result;

	result = getcwd(buf, sizeof(buf));
	if (result != NULL)
		printf("%s\n", buf);
	else
	{
		perror("MINISHELL");
		return (1);
	}
	return (0);
}
