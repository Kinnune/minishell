/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 15:45:43 by ekinnune          #+#    #+#             */
/*   Updated: 2023/07/17 15:55:05 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_last_in(char **redir)
{
	if (!*redir)
		return (1);
	if (!ft_strncmp(*redir, "<", ft_strlen(*redir))
		|| (!ft_strncmp(*redir, "<<", ft_strlen(*redir))))
		return (1);
	return (is_last_in(redir + 2));
}

void	pipe_doc(char *here_doc)
{
	int	filedes[2];

	pipe(filedes);
	dup2(filedes[0], STDIN_FILENO);
	write (filedes[1], here_doc, ft_strlen(here_doc + 1));
	close (filedes[0]);
	close (filedes[1]);
}

char	*handle_doc_line(char *line, char *total)
{
	char	*temp;

	temp = total;
	total = ft_calloc(ft_strlen(total)
			+ ft_strlen(line) + 3, sizeof(char));
	if (!total)
		exit(-1);
	ft_strlcpy(total, temp, ft_strlen(temp) + 1);
	ft_strlcpy((total + ft_strlen(total)), line, ft_strlen(line)
		+ ft_strlen(total) + 1);
	*(total + ft_strlen(total)) = '\n';
	free(temp);
	free(line);
	return (total);
}
