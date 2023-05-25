/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:51:25 by ekinnune          #+#    #+#             */
/*   Updated: 2023/05/15 10:35:00 by ekinnune         ###   ########.fr       */
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
