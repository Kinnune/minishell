/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokensis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:37:57 by ekinnune          #+#    #+#             */
/*   Updated: 2023/07/17 13:30:53 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tokenizer(const char *input)
{
	t_token	*head;
	t_token	*node;

	if (!input)
		return (NULL);
	head = NULL;
	while (*input)
	{
		while (*input == ' ')
			input++;
		if (!*input)
			break ;
		if (special_symbol(*input))
			node = handle_special_symbol(input);
		else
			node = handle_name_symbol(input);
		if (!node)
			return (free_tokens(head));
		input += node->size;
		append_token(&head, node);
	}
	if (head)
		head->prev = NULL;
	return (head);
}

int	check_tokens(t_token *token)
{
	if (!token)
		return (1);
	while (token)
	{
		if (token->type == PIPE)
		{
			if (!token->prev || !token->next)
				return (syntax_error());
		}
		if (token_type_redir(token))
		{
			if (!token_type_command(token->next))
				return (syntax_error());
		}
		token = token->next;
	}
	return (0);
}

t_token	*make_token(const char *pos, size_t size, enum e_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->str = ft_strndup(pos, size);
	if (!token->str)
	{
		free(token);
		return (NULL);
	}
	token->pos = pos;
	token->size = size;
	token->type = type;
	token->next = NULL;
	return (token);
}

void	append_token(t_token **list_ptr, t_token *node)
{
	t_token	*start;
	t_token	*list;

	if (!(*list_ptr))
	{
		(*list_ptr) = node;
		return ;
	}
	start = *list_ptr;
	list = *list_ptr;
	while (list->next)
		list = list->next;
	list->next = node;
	node->prev = list;
	list = start;
}

void	*free_tokens(t_token *list)
{
	if (!list)
		return (NULL);
	free_tokens(list->next);
	free(list->str);
	free(list);
	return (NULL);
}
