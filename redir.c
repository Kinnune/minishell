/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:51:25 by ekinnune          #+#    #+#             */
/*   Updated: 2023/06/28 19:05:40 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//lsof -p

void here_doc(char *key);

int	check_redirect_in(char **redir)
{
	if (!ft_strncmp(*redir, "<", ft_strlen(*redir)))
	{
		// dprintf(2, "setting in\n");
		redirect_in(0, *(redir + 1), STDIN_FILENO);
		return (1 + check_redirect_in(redir + 2));
	}
	else if (!ft_strncmp(*redir, "<<", ft_strlen(*redir)))
	{
		printf("heredoc\n");
		here_doc(*(redir + 1));
		return (1 + check_redirect_in(redir + 2));
	}
	else if (!ft_strncmp(*redir, ">", ft_strlen(*redir))
		|| !ft_strncmp(*redir, ">>", ft_strlen(*redir)))
		return (check_redirect_in(redir + 2));
	return (0);
}

/* here we trust the redirects come in pairs of 2 and they will */
int	check_redirect_out(char **redir)
{
	// dprintf(2, "'%s'\n", *redir);
	// dprintf(2, "'%s'\n", *(redir + 1));
	if (!ft_strncmp(*redir, ">", ft_strlen(*redir)))
	{
		// dprintf(2, "setting out >%s\n", *(redir + 1));
		redirect_out(0, *(redir + 1), STDOUT_FILENO);
		return (1 + check_redirect_out(redir + 2));
	}
	else if (!ft_strncmp(*redir, ">>", ft_strlen(*redir)))
	{
		// dprintf(2, "setting out >>\n");
		redirect_out(1, *(redir + 1), STDOUT_FILENO);
		return (1 + check_redirect_out(redir + 2));
	}
	else if (!ft_strncmp(*redir, "<", ft_strlen(*redir))
		|| !ft_strncmp(*redir, "<<", ft_strlen(*redir)))
		return (check_redirect_out(redir + 2));
	return (0);

}

int	check_redirect(t_command *command, int new_fd)
{
	if (!ft_strncmp(command->redir[0], "<", 1))
	{
		printf("setting in\n");
		redirect_in(0, *((command->redir) + 1), STDIN_FILENO);
		return (-1);
	}
	if (!ft_strncmp(command->redir[0], ">", ft_strlen(command->redir[0])))
	{
		printf("setting out\n");
		redirect_out(0, *((command->redir) + 1), STDOUT_FILENO);
		return (1);
	}
	return (0);
}

int	redirect_out(int append, char *filename, int new_fd)
{
	int fd;

//for open put rights
	if (append)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	redirect_in(int delimiter, char *filename, int new_fd)
{
	struct stat file_stat;
	char *buffer;
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (fd);
	dup2(fd, new_fd);
	// dup2(fd, STDIN_FILENO);
	close(fd);
	return (new_fd);
}

//write to pipe return pipe out close pipe in 
//and set redirect in to pipe out
void here_doc(char *key)
{
	char *line;
	char *total;
	char *temp;

	temp = NULL;
	total = NULL;
	line = readline("<");
	while (ft_strncmp(line, key, ft_strlen(line)))
	{
		temp = total;
		total = ft_calloc(ft_strlen(total) + ft_strlen(line) + 2, sizeof(char));
		if (!total)
			return ;
		ft_strlcpy(total, temp, ft_strlen(temp) + 1);
		ft_strlcpy((total + ft_strlen(total)), line, ft_strlen(line) + ft_strlen(total) + 1);
		*(total + ft_strlen(total)) = '\n';
		free(temp);
		free(line);
		line = readline("<");
	}
	free(line);
	// printf("[%s]",total);
	// write(STDOUT_FILENO, total, ft_strlen(total));
	free(total);
}
	// {
		// if (access(filename, F_OK))
		// 	fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT);
		// else
		// 	fd = open(filename, O_WRONLY | O_CREAT);
	// }
