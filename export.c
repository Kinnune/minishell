/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:43:50 by djames            #+#    #+#             */
/*   Updated: 2023/05/25 11:35:18 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include<string.h>

//extern char **environ;

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

void add_quotes(char* str) {
    
    int i;
    int flag;

    i=0;
    flag = 0;
    write(1, "declare -x ", 11);
    while(str[i] != '\0')
    {
        write(1, &(str[i]), 1);
        if(str[i] == '=' && str[i + 1] != '\0')
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
