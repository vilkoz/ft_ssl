# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/18 13:19:24 by vrybalko          #+#    #+#              #
#    Updated: 2018/01/31 19:34:43 by vrybalko         ###   ########.fr        #
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

SRCS = main.c											\
	   reader.c											\
	   base64/base64.c									\
	   base64/base64_run.c								\
	   base64/argparse/base64_argparse.c				\
	   base64/argparse/base64_argparse_funcs.c			\
	   des/des.c										\
	   des/des_run.c									\
	   des/des_operations.c								\
	   des/des_key_generation.c							\
	   des/des_initial_premutation.c					\
	   des/convert_hex_key.c							\
	   des/argparse/des_argparse.c						\
	   des/argparse/des_cbc_argparse.c					\
	   des/argparse/des_argparse_funcs.c				\
	   des/argparse/des_cbc_argparse_funcs.c			\
	   des3/des3_run.c									\
	   des3/des3_operations.c							\
	   des3/argparse/des3_argparse.c					\
	   des3/argparse/des3_ecb_argparse.c				\
	   des3/argparse/des3_argparse_funcs.c				\
	   des3/argparse/des3_argparse_general_funcs.c		\

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

test: $(NAME)
	cd src/base64; python3 base64_test.py
	cd src/des; python3 des_cbc_test.py
	cd src/des; python3 des_ecb_test.py
	cd src/des3; python3 des3_test.py
