/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putbased_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 12:29:49 by ekinnune          #+#    #+#             */
/*   Updated: 2022/12/09 13:07:56 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_based(long unsigned int n, int base)
{
	int		count;

	count = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		count++;
		n /= base;
	}
	return (count);
}

int	ft_putbased_fd(long unsigned int n, int base, char format, int fd)
{
	char	num_chr;

	if (n >= (unsigned int)base)
		ft_putbased_fd(n / base, base, format, fd);
	num_chr = '0' + (n % base);
	if (num_chr > '9')
		num_chr = num_chr - '0' + format - 10;
	ft_putchar_fd(num_chr, fd);
	return (ft_count_based(n, base));
}
