# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vrybalko <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/23 14:08:11 by vrybalko          #+#    #+#              #
#    Updated: 2018/01/18 17:48:18 by vrybalko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

VPATH = src

FLAGS = -Wall -Wextra -Werror -I include/ -g

SRCS = memory/ft_memset.c						\
	   memory/ft_bzero.c						\
	   memory/ft_memcpy.c						\
	   memory/ft_memccpy.c						\
	   memory/ft_memmove.c						\
	   memory/ft_memchr.c						\
	   memory/ft_memchr.c						\
	   memory/ft_memcmp.c						\
	   memory/ft_memalloc.c						\
	   memory/ft_memdel.c						\
	   memory/ft_realloc.c						\
	   string/ft_strlen.c						\
	   string/ft_strdup.c						\
	   string/ft_strcpy.c						\
	   string/ft_strncpy.c						\
	   string/ft_strcat.c						\
	   string/ft_strncat.c						\
	   string/ft_strlcat.c						\
	   string/ft_strchr.c						\
	   string/ft_strrchr.c						\
	   string/ft_strstr.c						\
	   string/ft_strnstr.c						\
	   string/ft_strcmp.c						\
	   string/ft_strncmp.c						\
	   string/ft_atoi.c							\
	   string/ft_isalpha.c						\
	   string/ft_isdigit.c						\
	   string/ft_isalnum.c						\
	   string/ft_isascii.c						\
	   string/ft_isprint.c						\
	   string/ft_toupper.c						\
	   string/ft_tolower.c						\
	   string/ft_strnew.c						\
	   string/ft_strdel.c						\
	   string/ft_strclr.c						\
	   string/ft_striter.c						\
	   string/ft_striteri.c						\
	   string/ft_strmap.c						\
	   string/ft_strmapi.c						\
	   string/ft_strequ.c						\
	   string/ft_strnequ.c						\
	   string/ft_strsub.c						\
	   string/ft_strjoin.c						\
	   string/ft_strtrim.c						\
	   string/ft_strsplit.c						\
	   string/ft_itoa.c							\
	   string/ft_count_words.c					\
	   string/ft_strlenchr.c					\
	   string/ft_strlen_chr.c					\
	   string/ft_strsplit_quote.c				\
	   string/ft_strsplit_arr_quote.c			\
	   string/ft_atoi_base.c					\
	   string/ft_atod.c							\
	   print/ft_putchar.c						\
	   print/ft_putstr.c						\
	   print/ft_putendl.c						\
	   print/ft_putnbr.c						\
	   print/ft_putchar_fd.c					\
	   print/ft_putstr_fd.c						\
	   print/ft_putendl_fd.c					\
	   print/ft_putnbr_fd.c						\
	   print/ft_print_array.c					\
	   list/ft_lstnew.c							\
	   list/ft_lstdelone.c						\
	   list/ft_lstdel.c							\
	   list/ft_lstadd.c							\
	   list/ft_lstiter.c						\
	   list/ft_lstmap.c							\
	   list/ft_lst_at.c							\
	   list/ft_lst_push_back.c					\
	   list/ft_lst_size.c						\
	   list/ft_lst_to_array.c					\
	   list/ft_lst_rev.c						\
	   get_next_line/get_next_line.c			\
	   queue/queue.c

BIN_DIR = bin/

BINS = $(addprefix $(BIN_DIR), $(SRCS:.c=.o))

TEST = main.c

TEST_BINS = $(TEST:.c=.o)

all: $(NAME)

$(NAME): $(BINS)
	ar rc $(NAME) $(BINS)
	ranlib $(NAME)

$(BIN_DIR)%.o: %.c
	@mkdir -p $(shell dirname $@)
	gcc $(FLAGS) -c -o $@ $<

clean:
	/bin/rm -f $(BINS)
	/bin/rm -f $(TEST_BINS)

fclean: clean
	/bin/rm -f $(NAME)_test
	/bin/rm -f $(NAME)

re: fclean all

f: all
	@date
	@echo "\033[38;5;93mLINKING:\033[0m"
	gcc -o $(NAME)_test $(TEST) $(NAME)
	@echo "\033[38;5;93mRUNNING:\033[0m"
	./$(NAME)_test
