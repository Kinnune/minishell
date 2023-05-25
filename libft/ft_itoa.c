/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 17:10:26 by ekinnune          #+#    #+#             */
/*   Updated: 2022/11/08 13:47:24 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_digit_count(int n)
{
	int		test;
	int		times;
	int		minus;

	if (n == 0)
		return (1);
	minus = 0;
	if (n < 0)
		minus = 1;
	times = 0;
	if (n >= 1000000000 || n <= -1000000000)
		return (10 + minus);
	if (n < 0)
		n *= -1;
	test = 1;
	while (test <= n)
	{
		test *= 10;
		times++;
	}
	return (times + minus);
}

static	char	*ft_itoa_result(char *itoed, int n, int digit_count)
{
	if (digit_count != 0)
		ft_itoa_result(itoed, n / 10, digit_count - 1);
	if (n < 0)
	{
		if (n > -10)
		{
			*itoed = '-';
			*(itoed + digit_count) = '0' - n;
		}
		else
			*(itoed + digit_count) = '0' - (n % 10);
	}
	else
	{
		if (n < 10)
			*(itoed + digit_count) = '0' + n;
		else
			*(itoed + digit_count) = '0' + (n % 10);
	}
	return (itoed);
}

char	*ft_itoa(int n)
{
	char	*itoed;
	int		digit_count;

	digit_count = ft_digit_count(n);
	itoed = (char *)malloc(sizeof(char) * (digit_count + 1));
	if (!itoed)
		return (NULL);
	*(itoed + digit_count) = '\0';
	return (ft_itoa_result(itoed, n, digit_count - 1));
}
