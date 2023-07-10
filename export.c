/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:43:50 by djames            #+#    #+#             */
/*   Updated: 2023/07/10 12:10:33 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include<string.h>

//extern char **environ;if alphanumerico and fix if start with a number or equal

char *find_equal(int flag, char *str)
{
    int i;
    int equal;

    i =0;
    equal =0;
    while(str[i] != '\0')
    {
        if(str[i] == '=')
            equal=1;
        i++;
    }
    if(flag == 0 && equal == 0)
    {
        return (NULL);
    }
    return (str);
}

char *find_equal_2(char *str)
{
    int i;
    int equal;
    char *temp;

    i =0;
    equal =0;
    temp = NULL;
    while(str[i] != '\0' && equal == 0)
    {
        if(str[i] == '=')
            equal=1;
        //temp[i] = str[i];
        i++;
    }
    //temp = malloc(sizeof)
    temp = malloc((i + 1) * (sizeof(char )));
    if(equal == 1)
        i--;
    equal=0;
    while(equal < i)
    {
        temp[equal] = str[equal];
        equal++;
    }
    temp[i] = '\0';
    return (temp);
}

void print_environment(int flag) 
{
    int i;
    char *temp;

    i=0;
    temp =NULL;
    if(flag == 0)
    {
        while(g_data.envir[i] != NULL)
        {
            temp = find_equal(1, g_data.envir[i]);
            add_quotes(temp);
            i++;
        }
    }else if(flag == 1)
    {
        i=0;
        while(g_data.envir[i] != NULL)
        {
            temp =find_equal(0, g_data.envir[i]);
            if(temp != NULL)
                printf("%s\n", temp);
            i++; 
        }
    }
} 

void add_quotes(char* str) 
{
    int i;
    int flag;

    i=0;
    flag = 0;
    write(1, "declare -x ", 11);
    while(str[i] != '\0')
    {
        write(1, &(str[i]), 1);
        if(str[i] == '=') //&& str[i + 1] != '\0')
        {    
            write(1, "\"", 1);
            flag = 1;
        }
        i++;
    }
   if(flag == 1)
        write(1, "\"", 1);
    write(1, "\n", 1);
}
/*
void ft_find(char *str)
{
    int i;
    int len;

    len =ft_strlen(target_string);
    i=0;
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

    
}*/

/*
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
*/