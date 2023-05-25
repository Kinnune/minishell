/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:33:43 by djames            #+#    #+#             */
/*   Updated: 2023/05/11 15:48:00 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_pwd() 
{
    char buf[BUFFER]; 
	char *result;

    result = getcwd(buf, sizeof(buf));
    if (result != NULL) 
        printf("%s\n", buf);
    else {
        perror("MINISHELL");
        return 1;
    }
    return 0;
}