/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 16:26:35 by ekinnune          #+#    #+#             */
/*   Updated: 2022/11/08 15:09:19 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str_new;
	char			*str_ret;
	unsigned int	i;

	i = 0;
	str_new = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!str_new)
		return (NULL);
	str_ret = str_new;
	while (*s)
	{
		*str_new = f(i, *s);
		str_new++;
		i++;
		s++;
	}
	*str_new = '\0';
	return (str_ret);
}
