/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:51:25 by ekinnune          #+#    #+#             */
/*   Updated: 2023/07/11 19:17:10 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//lsof -p

		//made this pipe stuff in 5 minutes to make cat work properly
		//might leak stuff and not work as expected
		// if (!*(redir + 2))
		// write (STDIN_FILENO, here_doc, ft_strlen(here_doc + 1));
/* here we trust the redirects come in pairs of 2 and they will */
int	check_redirect_in(char **redir, char *here_doc)
{
	int	filedes[2];

	if (!*redir)
		return (0);
	if (!ft_strncmp(*redir, "<", ft_strlen(*redir)))
	{
		if (redirect_in(0, *(redir + 1)) < 0)
			return (INT_MIN);
		return (1 + check_redirect_in(redir + 2, here_doc));
	}
	else if (!ft_strncmp(*redir, "<<", ft_strlen(*redir)))
	{
		if (!*(redir + 2))
		{
			pipe(filedes);
			dup2(filedes[0], STDIN_FILENO);
			write (filedes[1], here_doc, ft_strlen(here_doc + 1));
			close (filedes[0]);
			close (filedes[1]);
		}
		return (1 + check_redirect_in(redir + 2, here_doc));
	}
	else if (!ft_strncmp(*redir, ">", ft_strlen(*redir))
		|| !ft_strncmp(*redir, ">>", ft_strlen(*redir)))
		return (check_redirect_in(redir + 2, here_doc));
	return (0);
}

int	check_redirect_out(char **redir)
{
	int	fd;

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
	else if (!ft_strncmp(*redir, "<", ft_strlen(*redir))
		|| !ft_strncmp(*redir, "<<", ft_strlen(*redir)))
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
		exit (-1);
	close(fd);
	return (0);
}

int	redirect_in(int delimiter, char *filename)
{
	char	*buffer;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		write(STDERR_FILENO, "minishell: ", 11);
		write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
		// if the first redirection fail we print messague file is missing one
		write(STDERR_FILENO, "\n", 1);
		return (fd);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
		exit (-1);
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
// printf("line  = %s\nkey = %s\nlen = %d\n", line, key, ft_strncmp(line, key, ft_strlen(line) + ft_strlen(key)));
	while (ft_strncmp(line, key, ft_strlen(line) + ft_strlen(key)))
	{
		if (line)
		{
			temp = total;
			total = ft_calloc(ft_strlen(total)
					+ ft_strlen(line) + 3, sizeof(char));
			if (!total)
				return (NULL);
			ft_strlcpy(total, temp, ft_strlen(temp) + 1);
			ft_strlcpy((total + ft_strlen(total)), line, ft_strlen(line)
				+ ft_strlen(total) + 1);
			*(total + ft_strlen(total)) = '\n';
			free(temp);
			free(line);
		}
		line = readline("<");
	}
	if (line)
		free(line);
	if (!total)
	{
		total = ft_calloc(2, sizeof(char));
		if (!total)
			return (NULL);
		// return (ft_calloc(1, sizeof(char)));
	}
	*(total + ft_strlen(total)) = '\n';
	return (total);
}
