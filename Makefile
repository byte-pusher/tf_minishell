# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/07 15:26:00 by gjupy             #+#    #+#              #
#    Updated: 2022/11/30 17:45:17 by rkoop            ###   ########.fr        #
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
		lexer/lexer.c lexer/lexer_utils.c lexer/expansion.c lexer/expansion_utils.c \
		utils/lst/lst_utils_ct.c utils/lst/lst_utils_env.c utils/lst/lst_utils_rd.c utils/lst/lst_utils_t.c \
		utils/errors/errors_utils.c utils/free/free.c \
		env/env.c \
		executor/executor.c executor/executor_utils.c \
		builtin/builtin.c builtin/builtin_utils.c builtin/unset.c builtin/export.c builtin/cd.c builtin/pwd.c \
		executor/here_doc.c executor/here_doc_utils.c \
		executor/route_stdin.c executor/route_stdin_utils.c \
		executor/route_stdout.c executor/route_stdout_utils.c \

 
OBJ_DIR = ./objs/
OBJFILES := $(SRCS:.c=.o)
OBJS := $(addprefix $(OBJ_DIR), $(OBJFILES))


all: $(NAME)

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(addprefix $(OBJ_DIR), builtin) $(addprefix $(OBJ_DIR), env) $(addprefix $(OBJ_DIR), executor) \
	$(addprefix $(OBJ_DIR), lexer) $(addprefix $(OBJ_DIR), parser)
	@mkdir -p $(addprefix $(OBJ_DIR), utils/lst) $(addprefix $(OBJ_DIR), utils/free) $(addprefix $(OBJ_DIR), utils/errors)
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
	@rm minishell

inside: $(OBJS) $(LIBFT)
	ar -t $(NAME)

valgrind: re
	valgrind --quiet --tool=memcheck --leak-check=full --show-leak-kinds=all --suppressions=supp --track-fds=yes ./minishell

.PHONY: all clean fclean re git lib valgrind