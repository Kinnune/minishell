/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 15:26:50 by ekinnune          #+#    #+#             */
/*   Updated: 2022/11/08 14:44:02 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	str_len;
	char	*dup;
	char	*dup_start;

	str_len = ft_strlen(s1) + 1;
	dup = (char *)malloc(sizeof(char) * str_len);
	if (!dup)
		return (NULL);
	dup_start = dup;
	while (str_len)
	{
		*dup = *s1;
		dup++;
		s1++;
		str_len--;
	}
	return (dup_start);
}
