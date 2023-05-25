/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 15:19:42 by ekinnune          #+#    #+#             */
/*   Updated: 2022/11/16 13:52:44 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	i;
	size_t	max_len;

	if (start >= ft_strlen(s) || !*s)
		len = 0;
	max_len = ft_strlen(s + start);
	if (len > max_len)
		len = max_len;
	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (len && *(s + start + i))
	{
		*dst = *(s + start + i);
		dst++;
		i++;
		len--;
	}
	*dst = '\0';
	return (dst - i);
}
