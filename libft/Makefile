
NAME = libft.a

CFILES = ft_atoi.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_itoa.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_printf_utils_num.c \
			ft_printf_utils_str.c \
			ft_printf.c \
			ft_putbased_fd.c \
			ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_putstr_fd.c \
			ft_putstrn_fd.c \
			ft_split.c \
			ft_strchr.c \
			ft_strdup.c \
			ft_striteri.c \
			ft_strjoin.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strmapi.c \
			ft_strncmp.c \
			ft_strndup.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strtrim.c \
			ft_substr.c \
			ft_lstadd_back.c \
			ft_lstadd_front.c \
			ft_lstclear.c \
			ft_lstdelone.c \
			ft_lstiter.c \
			ft_lstlast.c \
			ft_lstmap.c \
			ft_lstnew.c \
			ft_lstsize.c \
			ft_tolower.c \
			ft_toupper.c

OFILES = $(CFILES:.c=.o)

CFLAGS = -Wall -Werror -Wextra -c

.PHONY: all clean fclean re reclean

all: $(NAME)

$(NAME): $(OFILES) libft.h
	cc $(CFLAGS) $(CFILES)
	ar -sr $(NAME) $(OFILES)

clean:
	rm -fr $(OFILES)

fclean: clean
	rm -fr $(NAME)

re: fclean all

reclean: re
	make clean
