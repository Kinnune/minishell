/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:15:36 by djames            #+#    #+#             */
/*   Updated: 2023/05/11 17:12:19 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int isvalidnumber(char *str)
{
	long long	trans;
	int			sign;
	int			i;

	trans = 0;
	sign = 1;
	i = 0;
	if((ft_strncmp(str, "-9223372036854775808", 20)) == 0)
		return (2);
	while (str[i] == ' ' || (str[i] >= 8 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{	if (str[i] == '-')
			sign = -1;
		i++;
		if (str[i] == '\0')
			return (-1);
	}
	while (((str[i]) >= '0') && ((str[i]) <= '9'))
	{
		trans = trans * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0' || (trans < 0) )
		return (-1);
	return (2);
}
int check_exit(char **str)
{
	int i;
	i =0;
	if(str[1] != NULL)
	{
		if(isvalidnumber(str[1]) == 2 && str[2] != NULL)
			i = 257;
		else if(isvalidnumber(str[1]) == 2)
			i = (int) do_exit(str);
		else 
			i = 256;
	}else 
		i =0;
	return (i);
}
