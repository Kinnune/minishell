/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:18:21 by djames            #+#    #+#             */
/*   Updated: 2023/07/03 14:49:09 by djames           ###   ########.fr       */
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

int check_built(char *promline)
{
	char **str;
	int i;

	str =NULL;
	i=257;
	if(promline)
	{	
		str= ft_split(promline, ' ');
		if(str[0] != NULL && ft_strncmp(str[0], "exit", 4) == 0)
		{
			i =check_exit(str);
		}else if(str[0] != NULL && ft_strncmp(str[0], "echo", 4) == 0)
		{
			printf("reconoce echo\n");
		}else if(str[0] != NULL && ft_strncmp(str[0], "cd", 2) == 0)
		{
			change_directory(str[1]);
		}else if(str[0] != NULL && ft_strncmp(str[0], "pwd", 3) == 0)
		{
			ft_pwd();
		}else if(str[0] != NULL && ft_strncmp(str[0], "export", 6) == 0)
		{
			export_start(str);
		}else if(str[0] != NULL && ft_strncmp(str[0], "unset", 6) == 0)
		{
			if(str[1] != NULL)
				remove_start(str);
		}else if(str[0] != NULL && ft_strncmp(str[0], "env", 3) == 0)
			print_environment(1);
	}
	array_free(str);
	return (i);

}