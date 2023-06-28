/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:44:35 by djames            #+#    #+#             */
/*   Updated: 2023/06/28 16:55:36 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//now i need to update oldpwd and pwd in the enviroments
int change_directory(char *path)
 {
	char *result;
	char buf[BUFFER];
    char **path1;

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
	return 0;
}
