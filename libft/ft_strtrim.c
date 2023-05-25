/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 15:40:06 by ekinnune          #+#    #+#             */
/*   Updated: 2022/11/08 15:25:55 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_in_set(char const c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

static char	*ft_alloc_trimmed(char const *s1, char const *set, size_t *i)
{
	char	*trimmed;

	while (ft_in_set(*s1, set))
		s1++;
	while (*s1)
	{
		s1++;
		(*i)++;
	}
	if ((*i) > 0)
	{
		s1--;
		while (ft_in_set(*s1, set))
		{
			(*i)--;
			s1--;
		}
	}
	trimmed = (char *)malloc(sizeof(char) * ((*i) + 1));
	if (!trimmed)
		return (NULL);
	return (trimmed);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	size_t	i;
	size_t	trim_i;

	i = 0;
	trimmed = ft_alloc_trimmed(s1, set, &i);
	if (!trimmed)
		return (NULL);
	while (ft_in_set(*s1, set))
		s1++;
	trim_i = 0;
	while (trim_i < i)
	{
		*(trimmed + trim_i) = *s1;
		trim_i++;
		s1++;
	}
	*(trimmed + trim_i) = '\0';
	return (trimmed);
}
