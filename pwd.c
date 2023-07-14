/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:33:43 by djames            #+#    #+#             */
/*   Updated: 2023/07/12 20:35:39 by djames           ###   ########.fr       */
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
