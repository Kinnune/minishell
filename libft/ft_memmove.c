/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 16:28:02 by ekinnune          #+#    #+#             */
/*   Updated: 2022/11/18 20:02:02 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dst_ptr;
	unsigned char	*src_ptr;

	dst_ptr = (unsigned char *)dst;
	src_ptr = (unsigned char *)src;
	if (src_ptr < dst_ptr)
	{
		src_ptr += len;
		dst_ptr += len;
		while (len)
		{
			dst_ptr--;
			src_ptr--;
			*dst_ptr = *src_ptr;
			len--;
		}
	}
	else
		ft_memcpy(dst_ptr, src_ptr, len);
	return (dst);
}
