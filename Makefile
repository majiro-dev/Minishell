# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: manujime <manujime@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/09 22:40:46 by manujime          #+#    #+#              #
#    Updated: 2023/06/15 20:03:33 by manujime         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
LIBFT = libft/libft.a

GREEN		=		\033[0;32m
RED			=		\033[0;31m
END			=		\033[0m

SRC =   srcs/main.c \
		srcs/exe_utils.c \
		srcs/builtins.c \
		srcs/init.c \
		srcs/clean_up.c \
		srcs/export_utils.c \
		srcs/parser.c \
		srcs/parser_sign.c \
		srcs/parser_list.c \
		srcs/built_ins_2.c \
		srcs/updates_at_start.c \
		srcs/pipes.c \
		srcs/redirects.c \
		srcs/signals.c \
		srcs/here_document.c \
		srcs/built_ins_3.c \

OBJ = $(SRC:.c=.o)

INC		= -I/Users/$(USER)/.brew/opt/readline/include

LFLAGS	= -L/Users/$(USER)/.brew/opt/readline/lib -lreadline

NAME = minishell

all: $(NAME) tmp

$(LIBFT):
	@make extra -C libft
	
$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LFLAGS) $(INC) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled$(END)"


%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

bonus: $(BONUS)

tmp:
	@mkdir tmp
	@touch tmp/.here_docminishell.tmp

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft
	@echo "$(RED)$(NAME) deleted$(END)"
	@rm -rf tmp

re: fclean all

.PHONY: all clean fclean re

