/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 01:27:37 by ekinnune          #+#    #+#             */
/*   Updated: 2022/11/08 00:36:03 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	size_total;

	if (!count || !size)
		return (ft_calloc(1, 1));
	size_total = size * count;
	if (size_total / count != size)
		return (NULL);
	ptr = malloc(size_total);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, size_total);
	return (ptr);
}
