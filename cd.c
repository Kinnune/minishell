/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:44:35 by djames            #+#    #+#             */
/*   Updated: 2023/06/30 17:04:20 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//now i need to update oldpwd and pwd in the enviroments here

void free_split(char **tem)
{
    int i;

    i=0;
    while(tem[i] != NULL)
    {
        free(tem[i]);
        i++;
    }
    free(tem);
}

int chance_oldpwd(int i, char *str)
{
    char **tem;
    char *str3;
    char *str2;

    //liberar mi temp
    tem = ft_split(g_data.envir[i], '=');
    str3 =((ft_strjoin("OLDPWD=", tem[1])));
    printf("%s\n", str3);
    add_string(str3);
    str2 = ((ft_strjoin("PWD=", str)));
    add_string(str2);
    free(str3);
    free(str2);
    free_split(tem);
    return (0);
}

int chance_pwd(char *str)
{
    int i;
    int flag;

    i=0;
    flag=0;
    printf("hola\n");
    while(g_data.envir[i] != NULL)
    {
        if (ft_strncmp(g_data.envir[i], "PWD", 3) == 0 && flag ==0)
        {
            chance_oldpwd(i, str);
            flag=1;
            printf("que\n");
        }
        i++;
    }
    return (0);
}

int change_directory(char *path)
 {
	char *result;
	char buf[BUFFER];
    char **path1;

    //if the redirection delete fix this
    if(path == NULL)
    {
        printf("esto es el home%s\n", g_data.envir[16]);
        path1=ft_split(g_data.envir[16], '=');
        printf("dividido%s\n", path1[1]);
        path = path1[1];
    }

    if (chdir(path) == 0) {
        printf("Directory changed successfully.\n");
		result = getcwd(buf, sizeof(buf));
        //chance_pwd(buf);
        if (result != NULL) {
            printf("Current working directory: %s\n", buf);
        } else {
            perror("MINISHELL");
            return 1;
        }
    } else {
        perror("MINISHELL");
        return 1;
    }
    chance_pwd(buf);
    
    return 0;
}
