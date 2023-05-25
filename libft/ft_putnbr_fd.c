/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 18:23:34 by ekinnune          #+#    #+#             */
/*   Updated: 2022/11/08 14:35:42 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n > 9 || n < -9)
		ft_putnbr_fd(n / 10, fd);
	if (n < 0)
	{
		if (n > -10)
		{
			ft_putchar_fd('-', fd);
			ft_putchar_fd('0' - n, fd);
		}
		else
			ft_putchar_fd('0' - (n % 10), fd);
	}
	else
	{
		if (n < 10)
			ft_putchar_fd('0' + n, fd);
		else
			ft_putchar_fd('0' + (n % 10), fd);
	}
}
