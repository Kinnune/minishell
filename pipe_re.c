#include "minishell.h"

int close_pipe(int **fd, int i)
{
    int j;

    j=0;
    while(j <= i)
    {
        close(fd[j][0]);
        close(fd[j][1]);
        j++;
    }
    return (0);  
}

int ft_free(int **fd, int *pid, int i)
{
    int j;

    j=0;
    while(j < i)
    {
        if(fd[j])
            free(fd[j]);
        j++;
    }
	free(fd);
	free(pid);
    return (0);
}
// arg[0][0] = {"ls", "madonna", NULL}

int piepe_function(t_command *list, int i)
{
	int **fd;
	pid_t *pid;
	int j;

	fd = malloc(sizeof(int *) * (i + 1));
	pid = malloc(sizeof(pid_t) * (i + 1));
	j=0;
	while(j <= i)
	{
		fd[j] = malloc(sizeof(int) * 2);
		j++;

	}
	
	j=ft_exec(list, i, fd, pid);
	return(j);
}


int	check_redirect_out(char **redir);
int	check_redirect_in(char **redir, char *here_doc);

int ft_exec(t_command *command, int i, int **fd, pid_t *pid)
{
	int j;
    int madona;

	j = 0;
	while(j <= i)
	{
		if(pipe(fd[j]) == -1)
			ft_free(fd, pid, i);//imprimir error
		pid[j] = fork();
		if(pid[j] == -1)
			ft_free(fd, pid, i);//imprimir error
		if(pid[j] == 0)
		{
			if (!check_redirect_in(command->redir, command->here_doc) && j != 0)
			{
				// dprintf(2, "putting stdin\n");
				dup2(fd[j - 1][0], STDIN_FILENO);
			}
			if (!check_redirect_out(command->redir) && j <= (i - 1))
			{
				// dprintf(2, "putting stdout\n");
				dup2(fd[j][1], STDOUT_FILENO); // saber redireccion
			}
			close_pipe(fd, i);
			if(execve(get_path(*command->cmd),command->cmd, g_data.envir) != 0)
			{
				printf("exiting cause of error\n");
				exit(0);
			}
		}
		// printf("command %s\n", get_path(*command->cmd));
		if (command->next)
			command = command->next;
		j++;
	}
	j = 0;
	madona = -1;
    while (j < i)
    {
        waitpid(pid[j], &madona, 0);
        j++;
    }
	close_pipe(fd, i);
	ft_free(fd, pid, i);
    return (madona);
}

void check_list(t_command *list)
{
    int i;
    t_command *temp;
    i=0;
    temp = list;
    while(temp != NULL)
    {
        temp= temp->next;
        i++;
    }
    piepe_function(list, i - 1);
}