/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:18:21 by djames            #+#    #+#             */
/*   Updated: 2023/07/09 16:32:17 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned char do_exit(char **str)
{
	
	unsigned char x;
	x=0;
	if(str[1] != NULL)
	{
		x =(unsigned char)ft_atoi(str[1]);
		
	}
	return (x);
}
void export_start(char **str)
{
	int i;
	int j;

	i=1;
	j = ft_length_word(str);
	if(str[1] == NULL) 
	{	
		print_environment(0);
		
	}else 
	{	
		while(i < j)
		{	
			add_string(str[i]);
			i++;
		}
	}
}

void remove_start(char **str)
{
	int i;
	int j;

	i=1;
	j= ft_length_word(str);
	while(i < j)
	{
		remove_string(str[i]);
		i++;
	}
}

void array_free(char **str)
{
	int i;

	i=0;
	while(str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int check_built(char **str)// change this
{
	int i;

	i=1;
	if(str)
	{	
		
		if(str[0] != NULL && ft_strncmp(str[0], "exit", 4) == 0)
		{
			i =check_exit(str);
			i=0;
		}else if(str[0] != NULL && ft_strncmp(str[0], "echo", 4) == 0)
		{
			start_echo(str);
			i=0;
		}else if(str[0] != NULL && ft_strncmp(str[0], "cd", 2) == 0)
		{
			change_directory(str[1]);
			i=0;
		}else if(str[0] != NULL && ft_strncmp(str[0], "pwd", 3) == 0)
		{
			ft_pwd();
			i=0;
		}else if(str[0] != NULL && ft_strncmp(str[0], "export", 6) == 0)
		{
			export_start(str);
			i=0;
		}else if(str[0] != NULL && ft_strncmp(str[0], "unset", 6) == 0)
		{
			if(str[1] != NULL)
				remove_start(str);
			i=0;
		}else if(str[0] != NULL && ft_strncmp(str[0], "env", 3) == 0)
		{
			print_environment(1);
			i=0;
		}
	}
	return (i);
}