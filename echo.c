/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:10:27 by djames            #+#    #+#             */
/*   Updated: 2023/07/10 15:37:17 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void echo(char **str, int newline) 
{
    int i;
    int j;

    i=1;
    if(newline == 0)
    {
        i= 2;
    }
    j=i;
    while(str[i] != NULL)
    {
        if(i == j)
            printf("%s", str[i]);
        else
            printf(" %s", str[i]);
        i++;
    }
    if (newline)
        printf("\n");
}

void start_echo(char **str)
{
    int i;

    i=1;
    if (str && *(str + 1) && ft_strlen(*(str + 1)) > 1)
    {
        if(str[1][0] == '-' && str[1][1] == 'n' && str[1][2] == '\0')
            i=0;
    }
    echo(str, i);
}