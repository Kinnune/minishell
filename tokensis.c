/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokensis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:37:57 by ekinnune          #+#    #+#             */
/*   Updated: 2023/06/15 18:02:58 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
accepted states
	quotes -> matching quote
	pipe -> something on left side
			if right side missing prompt for compeletion
	program name -> ends in ' ' or other recognized token
	redirections -> require only right field, the filename
	$ -> ?, valid name of variable
*/

// always interpret meta sequences / operators

// building the tree
// commands that have ** arguments and redirections
// commands are separated by pipes

t_token	*tokenizer(const char *input)
{
	t_token *head;
	t_token *node;

	if (!input)
		return (NULL);
	head = NULL;
	while (*input)
	{
		while (*input == ' ')
			input++;
		if (special_symbol(*input))
			node = handle_special_symbol(input);
		else
			node = handle_name_symbol(input);
		if (!node)
		{
			free_tokens(head);
			return (NULL);
		}
		input += node->size;
		append_token(&head, node);
	}
	return (head);
}

t_token	*make_token(const char *pos, size_t size, e_type type)
{
	t_token *token;

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

t_token	*is_progname(const char *input)
{
	size_t size;

	size = 0;
	while (!special_symbol(*(input + size)))
	{
		size++;
	}
	return (make_token(input, size, NAME));
}

t_token	*is_redir(const char *input)
{
	t_token *token;
	size_t size;
	e_type token_type;

	size = 0;
	if (*input == '<')
	{
		if (*(input + 1) == '<')
		{
			size = 2;
			token_type = RDIRDEL;
		}
		else
		{
			size = 1;
			token_type = RDIRIN;
		}
	}
	if (*input == '>')
	{
		if (*(input + 1) == '>')
		{
			size = 2;
			token_type = RDIRAPP;
		}
		else
		{
			size = 1;
			token_type = RDIROUT;
		}
	}
	return (make_token(input, size, token_type));
}

t_token	*is_pipe(const char *input)
{
	return (make_token(input, 1, PIPE));	
}

t_token	*is_var(const char *input)
{
	size_t size;

	if (*(input + 1) == '?')
		return (make_token(input, 2, EXVAR));
	size = 0;
	//while character is valid name character
	//to-do: quotes and expansions
	while (*(input + size) != '=' && *(input + size) != ' ' && *(input + size))
		size++;
	return (make_token(input, size, ENVAR));
}

t_token	*is_quote(const char *input)
{
	e_type token_type;
	size_t size;

	if (*input == '\'')
		token_type = SQUOTE;
	else
		token_type = DQUOTE;
	//to-do: handle variable expansion in DQUOTE
	size = 1;
	while (*(input + size) != *input)
	{
		if (!*(input + size))
			return (NULL);
		size++;
	}
	size++;
	return (make_token(input, size, token_type));
}

void	append_token(t_token **list_ptr, t_token *node)
{
	t_token *start;
	t_token *list;

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
	list = start;
}

t_token	*handle_name_symbol(const char *input)
{
	return (is_progname(input));
}

t_token *handle_special_symbol(const char *input)
{
	if (*input == '\'' || *input == '"')
		return (is_quote(input));
	else if (*input == '<' | *input == '>')
		return (is_redir(input));
	else if (*input == '|')
		return (is_pipe(input));
	else if (*input == '$')
		return (is_var(input));
	else
		return (NULL);
}

int		special_symbol(char input)
{
	return (input == '>' | input == '<' | input == '$'
		| input == '|' | input == '\''  | input == '"'
		| input == ' ' | input == '\t' | input == '\0');
}

void	print_tokens(t_token *token)
{
	while (token)
	{
		printf("{%lu %s, %d, %s}\n", token->size, token->str, token->type, token->pos);
		token = token->next;
	}
}

void	free_tokens(t_token *list)
{
	if (!list)
		return ;
	free_tokens(list->next);
	free(list->str);
	free(list);
}

// void	free_tokens(t_token *list)
// {
// 	t_token *temp;

// 	while (list)
// 	{
// 		temp = list->next;
// 		if (list->str)
// 			free(list->str);
// 		free(list);
// 		list = temp;
// 	}
// }
