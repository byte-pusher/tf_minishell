# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/07 15:26:00 by gjupy             #+#    #+#              #
#    Updated: 2022/11/26 16:46:03 by gjupy            ###   ########.fr        #
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

LDFLAGS     = -L/Users/$(USER)/.brew/opt/readline/lib
CPPFLAGS    = -I/Users/$(USER)/.brew/opt/readline/include

SRCS  = main.c \
		init.c \
		signal.c \
		parser/parser.c parser/parser_utils.c parser/cmd_parser.c parser/redir_parser.c \
		lexer/lexer.c lexer/lexer_utils.c \
		utils/lst/lst_utils_ct.c utils/lst/lst_utils_env.c utils/lst/lst_utils_rd.c utils/lst/lst_utils_t.c \
		utils/errors/errors_utils.c utils/free/free.c \
		env/env.c \
		executor/executor.c executor/executor_utils.c executor/route_stdin.c executor/route_stdout.c \
		builtin/builtin.c builtin/builtin_utils.c
 
OBJ_DIR = ./objs/
OBJFILES := $(SRCS:.c=.o)
OBJS := $(addprefix $(OBJ_DIR), $(OBJFILES))


all: $(NAME)

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) lib
	@$(CC) $(FLAGS) $(LDFLAGS) $(CPPFLAGS) $(OBJS) $(LIBFT) -lreadline  -o $(NAME)
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

valgrind: $(NAME)
	valgrind --quiet --tool=memcheck --leak-check=full --show-leak-kinds=all --suppressions=supp --track-fds=yes ./minishell

.PHONY: all clean fclean re git lib valgrind