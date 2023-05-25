/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_num.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 12:30:31 by ekinnune          #+#    #+#             */
/*   Updated: 2022/12/09 13:20:35 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_hexdes(va_list ap, char format)
{
	if (format == 'X')
		format = 'A';
	else
		format = 'a';
	return (ft_putbased_fd((unsigned int)va_arg(ap, long int), 16, format, 1));
}

int	ft_print_ptr(va_list ap)
{
	long unsigned int	too_long;

	ft_putstr_fd("0x", 1);
	too_long = (long unsigned int)va_arg(ap, long int);
	return (ft_putbased_fd(too_long, 16, 'a', 1) + 2);
}

int	ft_print_des(va_list ap, char format)
{
	long int	n;
	int			sign;

	sign = 0;
	n = va_arg(ap, int);
	if (format == 'u')
		n = (unsigned int)n;
	if (n < 0)
	{
		ft_putchar_fd('-', 1);
		n *= -1;
		sign = 1;
	}
	ft_putbased_fd(n, 10, 'a', 1);
	return (ft_count_based(n, 10) + sign);
}
