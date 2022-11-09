# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/07 15:26:00 by gjupy             #+#    #+#              #
#    Updated: 2022/11/09 17:36:17 by gjupy            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME  = minishell
CC    = gcc
FLAGS = -Wall -Werror -Wextra
SRCS  = main.c \
		init.c \
		./libft/ft_substr.c ./libft/lst_utils.c ./libft/ft_putstr_fd.c \
		./lexer/lexer.c ./lexer/lexer_utils.c \
		./parser/parser.c \
		./errors_utils.c

OBJS = $(SRCS:c=o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

clean:
	rm -f $(OBJS) $(OBJS_B)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

inside: $(OBJS) $(LIBFT)
	ar -t $(NAME)

git:
	git add .
	git commit -m "commit"
	git push

.PHONY: all clean fclean re git libft