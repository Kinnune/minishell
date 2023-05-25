/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 21:16:40 by ekinnune          #+#    #+#             */
/*   Updated: 2022/11/15 21:32:42 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	ret_len;

	if (!dst && !dstsize)
		return (ft_strlen(src));
	if (dstsize <= ft_strlen(dst))
		return (ft_strlen(src) + dstsize);
	ret_len = ft_strlen(src) + ft_strlen(dst);
	while (*dst && dstsize)
	{
		dst++;
		dstsize--;
	}
	ft_strlcpy(dst, src, dstsize);
	return (ret_len);
}
