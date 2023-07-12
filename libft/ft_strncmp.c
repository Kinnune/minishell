/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 22:15:13 by ekinnune          #+#    #+#             */
/*   Updated: 2023/07/12 14:32:46 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (!s1 || !s2)
		return (0);
	if (n == 0)
		return (0);
	i = 0;
	while (i < n && *(str1 + i))
	{
		if (*(str1 + i) - *(str2 + i) == 0)
			i++;
		else
			break ;
		if (i == n)
			return (0);
	}
	return (*(str1 + i) - *(str2 + i));
}
