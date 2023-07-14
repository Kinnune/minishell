/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:15:36 by djames            #+#    #+#             */
/*   Updated: 2023/07/14 16:53:52 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid2(char *str, long long trans, int i)
{
	int	flag;

	flag = 0;
	while (((str[i]) >= '0') && ((str[i]) <= '9'))
	{
		if (trans < 0)
			flag = 1;
		trans = trans * 10 + (str[i] - '0');
		i++;
	}
	printf("%lld\n", trans);
	if (str[i] != '\0' || (trans < 0) || flag == 1)
		return (-1);
	return (2);
}

int	isvalidnumber(char *str)
{
	long long	trans;
	int			sign;
	int			i;

	trans = 0;
	sign = 1;
	i = 0;
	if ((ft_strncmp(str, "-9223372036854775808", 20)) == 0)
		return (2);
	while (str[i] == ' ' || (str[i] >= 8 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		i++;
		if (str[i] == '\0')
			return (-1);
	}
	return (is_valid2(str, trans, i));
}

int	ft_exit(int i, char *str)
{
	if (i != 257)
	{
		if (i == 256)
		{
			printf("exit\n");
			printf("MINISHELL: exit: %s: numeric argument required\n", str);
			i = 255;
		}
		else if (i >= 0 && i <= 255)
			printf("exit\n");
		else if (i == 256)
		{
			printf("exit\n");
			printf("MINISHELL: exit: too many arguments\n");
			i = 255;
		}
	}
	if (i != 257)
		exit(i);
	return (i);
}

int	check_exit(char **str)
{
	int	i;

	i = 0;
	if (str[1] != NULL)
	{
		if (isvalidnumber(str[1]) == 2 && str[2] != NULL)
			i = 257;
		else if (isvalidnumber(str[1]) == 2)
			i = (int)do_exit(str);
		else
			i = 256;
	}
	else
		i = 0;
	ft_exit(i, str[1]);
	g_data.flag = i;
	return (i);
}
