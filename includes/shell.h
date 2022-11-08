/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:36:57 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/08 17:44:41 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# define PURPLE "\033[0;35m"
# define RESET "\033[0m"

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <stdbool.h>
# include <errno.h>

/* ************************************************************************** */
/* STRUCTS																	  */
/* ************************************************************************** */
enum e_TOKEN_TYPE
{
	PIPE,
	GREAT,
	LESS,
	GREATGREAT,
	LESSLESS,
	SQUOTE,
	DQUOTE,
	WHITE_SPACE,
	COMMAND
};

typedef struct s_token
{
	char			*name;
	int				end;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_data
{
	char	*input;
	t_token	*tokens;
}	t_data;

/* ************************************************************************** */
/* LEXER																	  */
/* ************************************************************************** */
void	ft_lexer(t_data *data);
bool	ft_is_space(char c);
int		ft_get_chartype(char *s, int *i);
void	ft_handle_squote(t_data *data, int *i, int type);
void	ft_handle_dquote(t_data *data, int *i, int type);

/* ************************************************************************** */
/* UTILS																	  */
/* ************************************************************************** */

/* LIBFT */
t_token	*ft_lstlast(t_token *lst);
void	ft_lstadd_back(t_token **lst, t_token *new);
t_token	*ft_lstnew(t_token **tokens);
void	ft_print_list(t_token **lst);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif