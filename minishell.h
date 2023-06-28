/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:10:29 by djames            #+#    #+#             */
/*   Updated: 2023/06/28 17:25:17 by ekinnune         ###   ########.fr       */
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

typedef struct	s_command
{
	char **cmd;
	char **redir;
	struct s_command *next;
}	t_command;

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

int ft_exec(t_command *command, int i, int **fd, pid_t *pid);
int piepe_function(t_command *list, int i);
int ft_free(int **fd, int *pid, int i);
int close_pipe(int **fd, int i);
void	check_list(t_command *command);


//------
typedef enum
{
	NAME,
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
	struct s_token *prev;
}	t_token;

int count_quotes(char *input);
int check_tokens(t_token *token);
void here_doc(char *key);
int	syntax_error(void);

//paths.c
void	print_environ(void);
char	*dot_slash_remove(char *path);
char	*get_path(char *command);

//redir.c
int			redirect_out(int append, char *filename, int new_fd);
int			redirect_in(int delimiter, char *filename, int new_fd);
int			check_redirect(t_command *command, int new_fd);

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

//commands.c
int token_type_command(t_token *token);
t_token *skip_i_token(t_token *token, int i);
int count_name(t_token *token);
int token_type_redir(t_token *token);
int count_redir(t_token *token);
int set_redir(t_command *command, t_token *token);
int set_name(t_command *command, t_token *token);
t_token *find_redir(t_token *token);
t_token	*skip_pipe(t_token *token);
t_command	*convert_tokens(t_token *token);
void print_commands(t_command *command);
void	free_commands(t_command *command);

//------
#endif
