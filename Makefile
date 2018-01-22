# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/18 13:19:24 by vrybalko          #+#    #+#              #
#    Updated: 2018/01/22 22:12:54 by vrybalko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=ft_ssl

FLAGS= -Wall -Wextra -Werror -g

VPATH=src

IDIR=include/

all: $(NAME)

LIBFT_DIR=libft
LIBFT=$(LIBFT_DIR)/libft.a

$(LIBFT):
	make -C $(LIBFT_DIR) -j8

SRCS = main.c							\
	   reader.c							\
	   base64/base64.c					\
	   base64/base64_run.c				\
	   base64/base64_argparse.c			\
	   base64/base64_argparse_funcs.c	\
	   des/des.c						\
	   des/des_run.c					\
	   des/des_argparse.c				\
	   des/des_operations.c				\
	   des/des_argparse_funcs.c			\
	   des/des_key_generation.c			\
	   des/des_initial_premutation.c	\

BIN_DIR = bin

BINS = $(addprefix $(BIN_DIR)/, $(SRCS:.c=.o))

$(BIN_DIR)/%.o: %.c
	@mkdir -p $(shell dirname $@)
	gcc $(FLAGS) -I $(IDIR) -I $(LIBFT_DIR) -c -o $@ $<

$(NAME): $(LIBFT) $(BINS)
	gcc $(FLAGS) -I $(IDIR) -I $(LIBFT_DIR) -o $(NAME) $(BINS) $(LIBFT)

clean:
	make -C $(LIBFT_DIR) clean
	/bin/rm -f $(BINS)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	/bin/rm -f $(NAME)

re: fclean all
