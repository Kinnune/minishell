/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:51:25 by ekinnune          #+#    #+#             */
/*   Updated: 2023/06/20 16:57:33 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//just a rough draft for now,
//everyting is subject to change

int	redirect_out(int append, char *filename)
{
	int fd;

	if (append)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND);
	else
	{
		if (access(filename, F_OK))
			fd = open(filename, O_WRONLY | O_TRUNC);
		else
			fd = open(filename, O_WRONLY | O_CREAT);
	}
	return (dup2(fd, 1));
}

// << not done

int	redirect_in(int delimiter, char *filename)
{
	struct stat file_stat;
	char *buffer;
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (fd);
	dup2(fd, 0);
	return (0);
}

void here_doc(char *key)
{
	char *line;
	char *total;
	char *temp;

	temp = NULL;
	total = NULL;
	line = readline("<<");
	while (ft_strncmp(line, key, ft_strlen(key)))
	{
		temp = total;
		total = ft_calloc(ft_strlen(total) + ft_strlen(line) + 2, sizeof(char));
		ft_strlcpy(total, temp, ft_strlen(temp) + 1);
		ft_strlcpy((total + ft_strlen(total)), line, ft_strlen(line) + ft_strlen(total) + 1);
		*(total + ft_strlen(total)) = '\n';
		free(temp);
		free(line);
		line = readline("<<");
	}
	printf("[%s]",total);
	free(line);
	free(total);
}
