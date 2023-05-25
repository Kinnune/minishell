/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 12:37:05 by ekinnune          #+#    #+#             */
/*   Updated: 2022/11/01 18:27:51 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	check;

	check = 0;
	while (*s)
	{
		if (*s == (char)c)
			check++;
		s++;
	}
	if (*s == '\0' && (char)c == '\0')
		return ((char *)s);
	if (check == 0)
		return (NULL);
	else
	{
		while (*s != (char)c)
			s--;
	}
	return ((char *)s);
}
