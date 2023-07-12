/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copyenv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:01:51 by djames            #+#    #+#             */
/*   Updated: 2023/07/12 15:54:51 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_length_word(char **envp)
{
	int i;

	i=0;
	while(envp[i] != NULL)
	{
		i++;
	}
	return (i);
}

void copy_env(char **envp)
{
	int lenght;
	int i;

	i=0;
	lenght = ft_length_word(envp);
	g_data.envir = malloc((lenght  + 1) * (sizeof(char *)));
	g_data.envir[lenght] = NULL;
	while(i < lenght)
	{
		g_data.envir[i] = ft_strdup(envp[i]);
		i++;
	}
	if(g_data.flag == 0)
	{
		g_data.flag=1;
		remove_string("OLDPWD");
		add_string("OLDPWD"); 
	}
}
void aux_remove()
{
	int lenght;
	int i;
	char **temp;

	i=0;
	lenght = ft_length_word(g_data.envir);
	temp = malloc((lenght + 1) * (sizeof(char *)));
	temp[lenght] = NULL;
	while(i < (lenght))
	{
		temp[i] = ft_strdup(g_data.envir[i]);
		i++;
	}
    free_array(g_data.envir);
    copy_env(temp);
	free_array(temp);
}
void ft_copy(int j)
{
	char **temp;
	int i;
	int lenght;

	i=0;
	lenght = ft_length_word(g_data.envir);
	temp = malloc((lenght) * (sizeof(char *)));
	temp[lenght - 1] = NULL;
	while(i < (lenght - 1))
	{
		if(i >= j)
		{
			//if (g_data.envir[i + 1] != NULL)
				temp[i] = ft_strdup(g_data.envir[i + 1]);
		}
		else
			temp[i] = ft_strdup(g_data.envir[i]);
		i++;
	}
    free_array(g_data.envir);
    copy_env(temp);
	free_array(temp);
}

int remove_string(char *target_string)
{
    int i = 0;
    int length = ft_strlen(target_string);
	char *remo;

	remo=(check_temp(target_string));
	if(remo == NULL)
	 	return (-1);
    while (g_data.envir[i] != NULL) 
	{
        if (ft_strncmp(g_data.envir[i], target_string, length) == 0) 
		{
			ft_copy(i);
			break;
        }
        i++;
    }
	return (0);
}

void free_array(char **temp) 
{
    int i;

	i=0;
	if (temp == NULL)
		return ;
    while (temp[i] != NULL) {
        free(temp[i]);
        i++;
    }
    free(temp);
}

int find_word(char *str)
{
	int i;
	int equal;
	int length;

	i=0;
	equal=0;
	length= ft_strlen(str);
	while(str[i] != '\0' && equal == 0)
    {
        if(str[i] == '=')
        {
            equal=1;
            //return (temp);
        }
		i++;
	}
	i=0;
	while (g_data.envir[i] != NULL) 
	{
        if (ft_strncmp(g_data.envir[i], str, length) == 0) 
		{
			if(equal == 1)
			{	
				ft_copy(i);
				return (0);
			}
			return (1);
		}
		i++;
	}
	return (0);
}

int add_string(char *new_string) 
{
    int lenght;
	int i;
	char *remo;
	char **temp;

	i=0;
	remo=(find_equal_2(new_string));
	if(remo == NULL)
		return (-1);
		free(remo);
	if((find_word(new_string)) == 1)
		return (0);
	remove_string(remo);
	lenght = ft_length_word(g_data.envir);
	temp = malloc((lenght  + 2) * (sizeof(char *)));
	temp[lenght + 1] = NULL;
	while(i < (lenght))
	{
		temp[i] = ft_strdup(g_data.envir[i]);
		i++;
	}
	temp[i] = ft_strdup(new_string);
    free_array(g_data.envir);
    copy_env(temp);
	free_array(temp);
	return (0);
}