/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 12:47:25 by ekinnune          #+#    #+#             */
/*   Updated: 2022/12/09 12:53:01 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_found_percent(const char **fstr, va_list ap)
{
	char	conv;
	int		ret_val;

	conv = *((*fstr) + 1);
	ret_val = 0;
	if (conv == '%')
		ret_val += ft_print_percent();
	else if (conv == 'p')
		ret_val += ft_print_ptr(ap);
	else if (conv == 'c')
		ret_val += ft_print_chr(ap);
	else if (conv == 's')
		ret_val += ft_print_str(ap);
	else if (conv == 'd' || conv == 'i' || conv == 'u')
		ret_val += ft_print_des(ap, conv);
	else if (conv == 'x' || conv == 'X')
		ret_val += ft_print_hexdes(ap, conv);
	else
	{
		(*fstr)++;
		return (0);
	}
	(*fstr) += 2;
	return (ret_val);
}

int	ft_printf(const char *fstr, ...)
{
	int		ret_len;
	va_list	ap;
	size_t	i;

	va_start(ap, fstr);
	ret_len = 0;
	while (*fstr)
	{
		if (*fstr == '%')
			ret_len += ft_found_percent(&fstr, ap);
		else
		{
			i = 0;
			while (*(fstr + i) && *(fstr + i) != '%')
				i++;
			ft_pustrn_fd((char *)fstr, i, 1);
			fstr += i;
			ret_len += i;
		}
	}
	va_end(ap);
	return (ret_len);
}
