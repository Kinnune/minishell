# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/24 10:58:46 by djames            #+#    #+#              #
#    Updated: 2023/07/18 14:08:42 by ekinnune         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = main.c main_helpers.c \
		function.c exit.c ft_history.c pwd.c cd.c \
		export.c copyenv.c redir.c tokensis.c paths.c \
		commands.c pipe_re.c expand_var.c echo.c function2.c pipe.c \
		start.c misc.c token_is.c command_helpers.c \
		expand_var_helpers.c free.c redir_helpers.c

OUT = $(SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra 
RL_L = -lreadline -L ~/.brew/opt/readline/lib
RL_I = -I ~/.brew/opt/readline/include

CC = cc

all: $(NAME)

$(NAME): $(OUT)
	$(MAKE) -C ./libft
	$(CC) $(FLAGS) $(OUT) $(RL_L) $(RL_I) libft/libft.a  -o $(NAME) 

%.o: %.c
	$(CC) $(FLAGS) -I. -c $< -o $@

clean:
	rm -rf $(OUT)
	$(MAKE) clean -C ./libft

fclean:
	rm -rf $(NAME) $(OUT)
	$(MAKE) fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re
