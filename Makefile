# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/07 15:26:00 by gjupy             #+#    #+#              #
#    Updated: 2022/11/17 17:36:02 by rkoop            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME  = minishell
CC    = gcc
FLAGS = -Wall -Werror -Wextra -g
GREEN = \033[1;32m
RED = \033[1;31m
YEL = \033[1;33m
EOL = \033[0m

LIBFTDIR ?= ./libft
LIBFT ?= $(LIBFTDIR)/libft.a

SRCS  = main.c \
		init.c \
		errors_utils.c \
		parser/parser.c \
		lexer/lexer.c lexer/lexer_utils.c lexer/lst_utils.c
 
OBJ_DIR = ./objs/
OBJFILES := $(SRCS:.c=.o)
OBJS := $(addprefix $(OBJ_DIR), $(OBJFILES))


all: $(NAME)

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) lib
	@$(CC) $(FLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)
	@echo "\n$(GREEN) >> minishell created.\n $(EOL)"
	
lib:
	@make -C libft
	@echo "\n$(YEL) >> LIBFT created.  $(EOL)"

clean:
	@make clean -C libft
	@rm -f $(OBJS) 
	@echo "\n$(YEL) 🗑 >> clean executed.  $(EOL)"

fclean: 
	@make fclean -C libft
	@rm -f $(OBJS) $(NAME)
	@echo "\n$(YEL) 🗑 >> fclean executed.  $(EOL)"

re: fclean $(NAME)

test:
	@make all
	@echo "\n$(GREEN) >> run minishell. $(EOL)"
	@./minishell

inside: $(OBJS) $(LIBFT)
	ar -t $(NAME)

git:
	git add .
	git commit -m "commit"
	git push

.PHONY: all clean fclean re git lib