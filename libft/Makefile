NAME := libft.a
CC := gcc

SRCS := ft_isascii.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isprint.c \
		ft_strlen.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strncmp.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_bzero.c \
		ft_atoi.c \
		ft_memset.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strnstr.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putchar_fd.c \
		ft_split.c \
		ft_itoa.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c \
		get_next_line.c \
		get_next_line_utils.c \
		ft_printf.c \
		print_int.c \
		print_char.c \
		print_str.c \
		print_u_int.c \
		print_hexa.c \
		print_ptr.c \
		utils_count.c

BONUS := ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c

OBJ_DIR = objs/
OBJFILES :=  $(SRCS:.c=.o)
OBJ := $(addprefix $(OBJ_DIR), $(OBJFILES))

CFLAGS ?= -Wall -Wextra -Werror

all: $(NAME)

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@ar r $(NAME) $(OBJ)

clean:
	@rm -rf $(OBJ) $(BONUS_OBJ)

fclean:
	@rm -f $(NAME)
	@rm -rf $(OBJ) $(BONUS_OBJ)

re: fclean all


.PHONY: fclean clean all re test 
