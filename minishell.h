/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:10:29 by djames            #+#    #+#             */
/*   Updated: 2023/05/25 11:35:18 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <termios.h>
# define BUFFER 1024

typedef struct s_data
{
	char **envir;
	struct termios orig_termios;
}			t_data;

t_data	g_data;

void print_environment(int flag);
void copy_env(char **envp);
int check_built(char *promline);
int isvalidnumber(char *str);
int check_exit(char **str);
unsigned char do_exit(char **str);
void ft_history(char *prom);
int ft_pwd();
int change_directory(char *path);
void remove_string(const char *target_string);
void add_string(char *new_string);
void free_array(char **temp);
void add_quotes(char* input) ;
int ft_length_word(char **envp);
#endif
