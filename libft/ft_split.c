/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 20:10:33 by ekinnune          #+#    #+#             */
/*   Updated: 2022/11/16 14:04:08 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_check_edges(const char *s, char c)
{
	char	**splitted;

	if (!*s)
	{
		splitted = (char **)malloc(sizeof(char *));
		*splitted = NULL;
		return (splitted);
	}
	if (!c)
	{
		splitted = (char **)malloc(sizeof(char *) * 2);
		*splitted = ft_strdup(s);
		*(splitted + 1) = NULL;
		return (splitted);
	}
	return (NULL);
}

static size_t	ft_word_size_and_count(const char *s, char c, char condition)
{
	int	i;

	i = 0;
	if (condition == 's')
	{
		while (*s != c && *s)
		{
			i++;
			s++;
		}
		return (i);
	}
	else
	{
		while (*s)
		{
			while (*s == c)
				s++;
			if (*s != c && *s)
				i++;
			while (*s != c && *s)
				s++;
		}
	}
	return (i);
}

static void	ft_free_2d(char **array_2d)
{
	char	**cpy;

	cpy = array_2d;
	while (*cpy)
	{
		free(*cpy);
		cpy++;
	}
	free(array_2d);
}

static char	**ft_loop_s(const char *s, char c, size_t word_c, char **splitted)
{
	size_t	word_s;
	char	**splitted_cpy;

	splitted_cpy = splitted;
	while (*s && word_c)
	{
		while (*s == c)
			s++;
		word_s = ft_word_size_and_count(s, c, 's');
		*splitted = ft_substr(s, 0, word_s);
		if (!*splitted)
		{
			ft_free_2d(splitted_cpy);
			return (NULL);
		}
		s += word_s;
		while (*s == c)
			s++;
		splitted++;
	}
	*splitted = NULL;
	return (splitted_cpy);
}

char	**ft_split(char const *s, char c)
{
	size_t	word_c;
	char	**splitted;

	splitted = ft_check_edges(s, c);
	if (splitted)
		return (splitted);
	word_c = ft_word_size_and_count((char *)s, c, 'c');
	splitted = (char **)malloc(sizeof(char *) * (word_c + 1));
	if (!splitted)
		return (NULL);
	ft_loop_s(s, c, word_c, splitted);
	if (!splitted)
		return (NULL);
	return (splitted);
}
