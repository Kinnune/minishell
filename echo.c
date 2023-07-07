/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:10:27 by djames            #+#    #+#             */
/*   Updated: 2023/07/07 16:46:25 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//void start_echo(char *str, )

void echo(const char* str, int newline) 
{
    if (newline)
        printf("%s\n", str); // con write 
    else
        printf("%s", str);
}