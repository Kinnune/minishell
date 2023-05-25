/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 01:29:19 by ekinnune          #+#    #+#             */
/*   Updated: 2022/11/08 00:19:42 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*move;
	t_list	*next;

	move = *lst;
	while (move)
	{
		next = move->next;
		ft_lstdelone(move, del);
		move = next;
	}
	*lst = NULL;
}
