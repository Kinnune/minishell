/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:51:25 by ekinnune          #+#    #+#             */
/*   Updated: 2023/07/18 13:51:16 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redirect_in(char **redir, char *here_doc)
{
	if (!*redir)
		return (0);
	if (!ft_strncmp(*redir, "<", ft_strlen(*redir)))
	{
		if (redirect_in(*(redir + 1)) < 0)
			return (INT_MIN);
		return (1 + check_redirect_in(redir + 2, here_doc));
	}
	else if (!ft_strncmp(*redir, "<<", ft_strlen(*redir)))
	{
		if (is_last_in(redir + 2))
			pipe_doc(here_doc);
		return (1 + check_redirect_in(redir + 2, here_doc));
	}
	else if (!ft_strncmp(*redir, ">", ft_strlen(*redir)) || !ft_strncmp(*redir,
			">>", ft_strlen(*redir)))
		return (check_redirect_in(redir + 2, here_doc));
	return (0);
}

int	check_redirect_out(char **redir)
{
	if (!*redir)
		return (0);
	if (!ft_strncmp(*redir, ">", ft_strlen(*redir)))
	{
		if (redirect_out(0, *(redir + 1)) < 0)
			return (INT_MIN);
		return (1 + check_redirect_out(redir + 2));
	}
	else if (!ft_strncmp(*redir, ">>", ft_strlen(*redir)))
	{
		if (redirect_out(1, *(redir + 1)) < 0)
			return (INT_MIN);
		return (1 + check_redirect_out(redir + 2));
	}
	else if (!ft_strncmp(*redir, "<", ft_strlen(*redir)) || !ft_strncmp(*redir,
			"<<", ft_strlen(*redir)))
		return (check_redirect_out(redir + 2));
	return (0);
}

int	redirect_out(int append, char *filename)
{
	int	fd;

	if (!*filename)
	{
		write(STDERR_FILENO, "minishell: No such file or directory\n", 37);
		return (-1);
	}
	if (append)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (dup2(fd, STDOUT_FILENO) < 0)
		exit(-1);
	close(fd);
	return (0);
}

int	redirect_in(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		write(STDERR_FILENO, "minishell: ", 11);
		write(STDERR_FILENO, filename, ft_strlen(filename));		
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
		write(STDERR_FILENO, "\n", 1);
		return (fd);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
		exit(-1);
	close(fd);
	return (0);
}

char	*here_doc(char *key)
{
	char	*line;
	char	*total;
	char	*temp;

	temp = NULL;
	total = NULL;
	line = readline("<");
	signal(SIGINT, handle_signal);
	while (ft_strncmp(line, key, ft_strlen(line) + ft_strlen(key))
		&& g_data.flag2 != 1)
	{
		if (line)
			total = handle_doc_line(line, total);
		line = readline("<");
	}
	if (line)
		free(line);
	if (!total)
	{
		total = ft_calloc(2, sizeof(char));
		if (!total)
			return (NULL);
	}
	*(total + ft_strlen(total)) = '\n';
	return (total);
}
