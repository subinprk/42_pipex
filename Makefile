# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: siun <siun@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/03 10:43:28 by subpark           #+#    #+#              #
#    Updated: 2023/10/08 18:58:20 by siun             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		 = pipex
CC			 = cc
CCFLAGS		= -Werror -Wall -Wextra

LIBFT		= libft.a
LIBFT_DIR	= libft
LIBFT_PATH	= $(LIBFT_DIR)/$(LIBFT)

PRINTF		= libftprintf.a
PRINTF_DIR	= ft_printf
PRINTF_PATH	= $(PRINTF_DIR)/$(PRINTF)

SRC		= src/utils.c src/main.c
OBJ			= $(SRC:.c=.o)

all : $(NAME)

clean:
			rm -f $(OBJ)
			make clean -C $(LIBFT_DIR)
			make clean -C $(PRINTF_DIR)
fclean: clean
			rm -f $(NAME)
			rm -f $(PRINTF)
			rm -f $(LIBFT)
re : fclean all

%.o: %.c src/pipex.h
			$(CC) $(CCFLAGS) -c $< -o $@
$(LIBFT):
			make bonus -C $(LIBFT_DIR)
			mv $(LIBFT_DIR)/$(LIBFT) .
$(PRINTF):
			make -C $(PRINTF_DIR)
			mv $(PRINTF_DIR)/$(PRINTF) .
$(NAME): $(OBJ) $(LIBFT) $(PRINTF)
			$(CC) $(CCFLAGS) -o $@ $^
.PHONY: all clean fclean re