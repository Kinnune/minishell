/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:10:29 by djames            #+#    #+#             */
/*   Updated: 2023/05/25 12:08:46 by ekinnune         ###   ########.fr       */
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
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# include <errno.h>
# include <sys/stat.h>
# include <unistd.h>

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

//------
typedef enum
{
	PROG,
	ARGS,
	DQUOTE,
	SQUOTE,
	RDIRIN,
	RDIROUT,
	RDIRAPP,
	RDIRDEL,
	PIPE,
	ENVAR,
	EXVAR
} e_type;

//build all command in this format
//pipe stuff according to linked list order

typedef struct s_token
{
	const char *pos;
	char *str;
	size_t size;
	e_type type;
	struct s_token *next;
}	t_token;

//error.c
void	print_error(int error_nbr, char *error_str);

//paths.c
void	print_environ(void);
int		run_command(char *command, char **args);

//redir.c
int			redirect_out(int append, char *filename);
int			redirect_in(int delimiter, char *filename);

typedef struct s_command
{
	char	*arg;
	char	**argv;
	int		argc;
	char	*output;
	struct s_command *next;
}	t_command;
//lst.c
int			lst_size(t_command *list);
void		lst_print_args(t_command *list);
void		lst_free(t_command *list);
t_command	*build_commands(char *input);

//tokensis.c
t_token	*tokenizer(const char *input);
t_token	*is_progname(const char *input);
t_token	*is_quote(const char *input);
t_token	*is_var(const char *input);
t_token	*is_pipe(const char *input);
t_token	*is_redir(const char *input);
void	append_token(t_token **list, t_token *node);
t_token	*handle_name_symbol(const char *input);
t_token *handle_special_symbol(const char *input);
int	special_symbol(char input);
t_token	*make_token(const char *pos, size_t size, e_type type);
void print_tokens(t_token *token);
void	free_tokens(t_token *list);

//------
#endif
