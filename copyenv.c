/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copyenv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:01:51 by djames            #+#    #+#             */
/*   Updated: 2023/07/03 15:40:19 by djames           ###   ########.fr       */
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

void remove_string(const char *target_string)
{
    int i = 0;
    int length = ft_strlen(target_string);

    while (g_data.envir[i] != NULL) {
        if (ft_strncmp(g_data.envir[i], target_string, length) == 0) {
            free(g_data.envir[i]);
            int j = i;
            while (g_data.envir[j] != NULL) {
                g_data.envir[j] = g_data.envir[j + 1];
                j++;
            }
            i--; 
        }
        i++;
    }
	aux_remove();
}

void free_array(char **temp) {
    if (temp != NULL) {
        int i = 0;
        while (temp[i] != NULL) {
            free(temp[i]);
            i++;
        }
        free(temp);
    }
}

void add_string(char *new_string) 
{
    int lenght;
	int i;
	char *remo;
	char **temp;

	i=0;
	remo=(find_equal_2(new_string));
	remove_string(remo);
	free(remo);
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
}
