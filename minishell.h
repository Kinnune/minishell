/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:10:29 by djames            #+#    #+#             */
/*   Updated: 2023/07/18 17:07:26 by djames           ###   ########.fr       */
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
	int					flag3;
	struct termios		term;
}						t_data;

t_data					g_data;

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

typedef struct s_token
{
	const char			*pos;
	char				*str;
	size_t				size;
	enum e_type			type;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

int						check_built3(t_token *token, t_command *command);
int						start_main(t_token *token, t_command *command);
void					print_environment(int flag);
void					copy_env(char **envp);
int						check_built(char **str, int flag);
int						isvalidnumber(char *str);
int						check_exit(char **str, int flag);
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
void					command_not_found(char *command);
void					ft_exec35(t_command *command, int i, int **fd, int j);
void					ft_start3(char *prom_line);
void					handle_signal(int signal);

int						ft_exec(t_command *command, int i, int **fd,
							pid_t *pid);
int						piepe_function(t_command *list, int i);
int						ft_free(int **fd, int *pid, int i);
int						close_pipe(int **fd, int i);
int						check_list(t_command *command);
char					*check_temp(char *str, int flag, char *str2);
void					match_aux(int path_i, char **path_split, char *path_ptr,
							char *command);

int						check_tokens(t_token *token);
char					*here_doc(char *key);

int						is_builtin(char *command);

//misc.c
int						count_quotes(char *input);
int						syntax_error(void);
void					print_errorexport(char *str, int flag);
void					start_env(char **str);

//expand_var.c
char					*expand_var(char *str);
int						expand_command_args(t_command *command);
void					remove_quotes(char **str2d);
char					*set_varname(char *str);
void					get_varname(char **name);

//expand_var_helpers.c
void					handle_exvar(int *i, char **buff);
void					handle_varname(int *i, char **buff, char *str);
void					handle_blank(int *i, char **buff, char *str);
char					*check_var_logic(char **str);
int						valid_varname(char c);

//paths.c
char					*dot_slash_remove(char *path);
char					*get_path(char *command);

//redir_helpers.c
char					*handle_doc_line(char *line, char *total);
void					pipe_doc(char *here_doc);
int						is_last_in(char **redir);

//redir.c
int						redirect_out(int append, char *filename);
int						redirect_in(char *filename);
int						check_redirect(t_command *command, int new_fd);
int						check_redirect_out(char **redir);
int						check_redirect_in(char **redir, char *here_doc);

//token_is.c
t_token					*is_pipe(const char *input);
t_token					*is_var(const char *input);
t_token					*is_quote(const char *input);
t_token					*is_progname(const char *input);
t_token					*is_redir(const char *input);

//tokensis.c
t_token					*tokenizer(const char *input);
void					append_token(t_token **list, t_token *node);
t_token					*handle_name_symbol(const char *input);
t_token					*handle_special_symbol(const char *input);
int						special_symbol(char input);
t_token					*make_token(const char *pos, size_t size,
							enum e_type type);
void					print_tokens(t_token *token);
void					*free_tokens(t_token *list);

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

#endif
