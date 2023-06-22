/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 12:48:45 by djames            #+#    #+#             */
/*   Updated: 2023/06/16 10:17:30 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
/*
int main(int argc, char* argv[])
{
	int fd[2];
	// fd[0] read fd[1] write close (fd[1]) close file descriptors close(fd[0]) close one of the pipes 4 close callse heredan entonces hay que cerrar el doble de file descriptors
	if(pipe(fd) == -1)
		return 1;
	int pid1 = fork();
	if(pid1 < 0)
		return 2;
	if(pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp("ping", "ping", "-c", "google.com", NULL);
	}
	int pid2 = fork();
	if(pid12

	waitpid(pid1, NULL, 0);

	return 0;
}*/

int main(int argc, char * argv[], char **envp)
{
	char *nombre[] = {"cat", NULL};
	char *nombre2[]= {"ls", "madonna", NULL}; // for example this  cat | cat | ls |
	int	madona = -1;
	int fd1[2];
	int	fd2[2];
	if(pipe(fd1) == -1)
		return (1);
	int pid = fork();
	if(pid < 0)
		return (2);
	if(pid == 0)
	{
		dup2(fd1[1], STDOUT_FILENO);
		close(fd1[0]);
		close(fd1[1]);
		if(execve("/bin/cat", nombre, envp) != 0){
			printf("madona");
			exit(0);
		}
	}
	if(pipe(fd2) == -1)
		return (1);
	int pid2 = fork();
	if(pid2 < 0)
		return (3);
	if(pid2 == 0)
	{	
		dup2(fd1[0], STDIN_FILENO);
		close(fd1[0]);
		close(fd1[1]);
		dup2(fd2[1], STDOUT_FILENO);
		close(fd2[1]);
		close(fd2[0]);
		execve("/bin/cat", nombre, envp);
	}
	int pid3 = fork();
	if(pid3 < 0)
		return (4);
	if(pid3 == 0)
	{
		dup2(fd2[0], STDIN_FILENO);
		close(fd2[0]);
		close(fd2[1]);
		close(fd1[0]);
		close(fd1[1]);
		execve("/bin/ls", nombre2, envp);
	}
	close(fd1[0]);
	close(fd1[1]);
	close(fd2[0]);
	close(fd2[1]);
	int i =0;
	//while(i <= 2)
	//{
		//waitpid(-1, &madona, 0);
		//i++;
	//}
	
	waitpid(pid, &madona, 0);//-1 es lo mejor
	waitpid(pid2, &madona, 0);
	waitpid(pid3, &madona, 0);
	printf("%d\n", WEXITSTATUS(madona));
	return (0);
}