# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/24 15:39:40 by gjupy             #+#    #+#              #
#    Updated: 2022/11/08 13:46:10 by gjupy            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME  = pipex
CC    = gcc
FLAGS = -Wall -Werror -Wextra
LIBFT = ./libs/libft/libft.a
SRCS  = ./srcs/main.c \
		./srcs/error.c \
		./srcs/commands.c \
		./srcs/err_parser/parser.c ./srcs/err_parser/parser_utils.c \
		./srcs/utils.c \
		./srcs/pipes.c \
		./srcs/childs.c \
		./get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c

OBJS = $(SRCS:c=o)

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C libs/libft
	$(CC) $(FLAGS) $(OBJS) $(LIBFT) -o $(NAME)

clean:
	rm -f $(OBJS) $(OBJS_B)
	$(MAKE) -C libs/libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libs/libft fclean

re: fclean $(NAME)

inside: $(OBJS) $(LIBFT)
	ar -t $(NAME)

.PHONY: all clean fclean re libft