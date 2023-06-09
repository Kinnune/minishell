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
    while(j <= i)
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
int ft_exec(t_command *command, int i, int **fd, pid_t *pid)
{
	int j;
    int madona;
	char	*path_ptr;

	j = 0;
	madona =258;
	while(j <= i)
	{
		if(pipe(fd[j]) == -1)
			ft_free(fd, pid, i);//imprimir error
		pid[j] = fork();
		if(pid[j] == -1)
			ft_free(fd, pid, i);//imprimir error
		if(pid[j] == 0)
		{
			disableRawMode();
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			//  reformat these two if statements
			madona = check_redirect_in(command->redir, command->here_doc);
			if (madona < 0)
				exit(errno);
			if (!madona && j != 0)
				dup2(fd[j - 1][0], STDIN_FILENO);
			madona = check_redirect_out(command->redir);
			if (madona < 0)
				exit(errno);
			if (!madona && j <= (i - 1))
				dup2(fd[j][1], STDOUT_FILENO);
			close_pipe(fd, j);// ask if there is built in
			madona = check_built(command->cmd);// here
			if (madona != 1)
			{
				exit(madona);
			}	
			else if(execve(get_path(*command->cmd),command->cmd, g_data.envir) != 0)
			{
				dprintf(2, "minishell: %s: command not found\n", *command->cmd);
				exit(-1);
			}
		}
		if (command->next)
			command = command->next;
		j++;
	}
	j = 0;
	madona = -1;
	//pipes reading end existing causes cat | ls to not function properly
	//moved close pipes here from below hope everything still works 
	//desctivar el senal
	close_pipe(fd, i);
	while (j <= i)
	{
		waitpid(pid[j], &madona, 0);
		j++;
	}
	// close_pipe(fd, i);
	g_data.flag=WEXITSTATUS(madona);
	if (WIFSIGNALED(madona))
	{
		g_data.flag = 128 + WTERMSIG(madona);
		if (g_data.flag == SIGQUIT)
			write(STDERR_FILENO, "Quit: 3\n", 8);
		else if (g_data.flag == SIGSEGV)
			write(STDERR_FILENO, "Segmentation fault: 11\n", 23);
	}
	ft_free(fd, pid, i);
    return (madona);
}

int check_list(t_command *list)
{
    int i;
	int j;
    t_command *temp;
    i=0;
    temp = list;
	j=0;
    while(temp != NULL)
    {
        temp= temp->next;
        i++;
    }
    j=piepe_function(list, i - 1);
	return (j);
}