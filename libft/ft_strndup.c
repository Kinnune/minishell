/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:27:43 by ekinnune          #+#    #+#             */
/*   Updated: 2023/05/17 14:59:55 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *str, size_t len)
{
	char	*dup;
	char	*dup_start;

	dup = (char *)malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	dup_start = dup;
	*(dup + len) = '\0';
	while (len > 0)
	{
		len--;
		*(dup + len) = *(str + len);
	}
	return (dup_start);
}
