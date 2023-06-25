/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_re.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:58:49 by djames            #+#    #+#             */
/*   Updated: 2023/06/19 16:34:32 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

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
		//run_command(ls, )
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
// arg[0][0] = {"ls", "madonna", NULL}
int piepe_function(s_comand *list, int i)
{
	int **fd;
	pid_t *pid;
	int j;

	fd = malloc(sizeof(int *) * i);
	pid = malloc(sizeof(pid_t) * i);
	j=0;
	while(j < i)
	{
		fd[j] = malloc(sizeof(int) * 2);
		j++;
	}
	
	j=ft_exec(list, i, fd, pid);
	return(j);
}

int ft_exec(s_command *list, int i, int **fd, pid_t *pid)
{
	int j;

	j=0;
	while(j < i)
	{
		if(pipe(fd[j]) == -1)
			ft_free(fd, pid, i);//imprimir error
		if((pid[j] = fork() == -1))
			ft_free(fd, pid, i);//imprimir error
		if(pid[j] == 0)
		{
			if (j < (i - 1))
			{
				dup2(fd[j][1], STDOUT_FILENO); // saber redireccion
				
			//close_pipe(fd, i);
			}
			if (j != 0)
				dup2(fd[j - 1][0], STDIN_FILENO);
			close_pipe(fd, i);
			
			if(execve("/bin/cat", nombre, envp) != 0)//path, which comman redireccion
			{
				exit(0);
			}
		}


	}

}