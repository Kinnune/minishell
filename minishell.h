/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:10:29 by djames            #+#    #+#             */
/*   Updated: 2023/07/17 14:33:37 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <termios.h>
# include <unistd.h>

# define BUFFER 1024

typedef struct s_command
{
	char				**cmd;
	char				**redir;
	char				*here_doc;
	struct s_command	*next;
}						t_command;

typedef struct s_data
{
	char				**envir;
	int					flag;
	int					flag1;
	int					flag2;
	struct termios		term;
}						t_data;

t_data					g_data;

void					print_environment(int flag);
void					copy_env(char **envp);
int						check_built(char **str);
int						isvalidnumber(char *str);
int						check_exit(char **str);
unsigned char			do_exit(char **str);
void					ft_history(char *prom);
int						ft_pwd(void);
int						change_directory(char *path);
int						remove_string(char *target_string);
void					add_string(char *new_string);
void					free_array(char **temp);
void					add_quotes(char *input);
int						ft_length_word(char **envp);
char					*find_equal_2(char *str);
void					remove_start(char **str);
void					disable_rawmode(void);
void					enable_rawmode(void);
void					start_echo(char **str);
int						check_built2(char **str);
void					export_start(char **str);
char					*find_helper(int equal, int j, int i);
int						find_word(char *str);
void					ft_copy(int j);
int						ft_execaux(int i, pid_t *pid, int **fd);
void					ft_exec35(t_command *command, int i, int **fd, int j);
void					ft_start3(char *prom_line);
void					handle_signal(int signal);
void					print_errorexport(char *str);

int						ft_exec(t_command *command, int i, int **fd,
							pid_t *pid);
int						piepe_function(t_command *list, int i);
int						ft_free(int **fd, int *pid, int i);
int						close_pipe(int **fd, int i);
int						check_list(t_command *command);
char					*check_temp(char *str);
//------
enum					e_type
{
	NAME,
	DQUOTE,
	SQUOTE,
	RDIRIN,
	RDIROUT,
	RDIRAPP,
	RDIRDOC,
	PIPE,
	ENVAR,
	EXVAR
};

//build all command in this format
//pipe stuff according to linked list order

typedef struct s_token
{
	const char			*pos;
	char				*str;
	size_t				size;
	enum e_type			type;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

int						count_quotes(char *input);
int						check_tokens(t_token *token);
char					*here_doc(char *key);
int						syntax_error(void);

//expand_var.c
int						valid_varname(char c);
int						expand_command_args(t_command *command);
char					*expand_var(char *str);
char					*check_var_logic(char **str);
int						check_dollar(char *str);

//paths.c
void					print_environ(void);
char					*dot_slash_remove(char *path);
char					*get_path(char *command);

//redir.c
int						redirect_out(int append, char *filename);
int						redirect_in(int delimiter, char *filename);
int						check_redirect(t_command *command, int new_fd);
int						check_redirect_out(char **redir);
int						check_redirect_in(char **redir, char *here_doc);

//tokensis.c
t_token					*tokenizer(const char *input);
t_token					*is_progname(const char *input);
t_token					*is_quote(const char *input);
t_token					*is_var(const char *input);
t_token					*is_pipe(const char *input);
t_token					*is_redir(const char *input);
void					append_token(t_token **list, t_token *node);
t_token					*handle_name_symbol(const char *input);
t_token					*handle_special_symbol(const char *input);
int						special_symbol(char input);
t_token					*make_token(const char *pos, size_t size,
							enum e_type type);
void					print_tokens(t_token *token);
void					free_tokens(t_token *list);

//commands.c
int						token_type_command(t_token *token);
t_token					*skip_i_token(t_token *token, int i);
int						count_name(t_token *token);
int						token_type_redir(t_token *token);
int						count_redir(t_token *token);
int						set_redir(t_command *command, t_token *token);
int						set_name(t_command *command, t_token *token);
t_token					*find_redir(t_token *token);
t_token					*skip_pipe(t_token *token);
t_command				*convert_tokens(t_token *token);
void					print_commands(t_command *command);
void					free_2d(char **array);
void					free_commands(t_command *command);

//------
int						start_main(t_token *token, t_command *command);
int						check_built3(t_token *token, t_command *command);
#endif
