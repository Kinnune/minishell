/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 01:51:47 by ekinnune          #+#    #+#             */
/*   Updated: 2022/11/09 00:45:56 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_loop_needle(const char *s1, const char *s2, size_t i, size_t len)
{
	int	j;

	j = 0;
	while (*(s1 + i) == *(s2 + j) && len)
	{
		i++;
		j++;
		if (!*(s2 + j))
			return (1);
		len--;
	}
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	back_track;

	back_track = 0;
	if (!*needle)
		return ((char *)haystack);
	while (len && *(haystack + back_track))
	{
		if (ft_loop_needle(haystack, needle, back_track, len))
			return ((char *)(haystack + back_track));
		len--;
		back_track++;
	}
	return (NULL);
}
