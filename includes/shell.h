/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:36:57 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/16 16:59:02 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# define PURPLE "\033[0;35m"
# define RESET "\033[0m"
# define COLOR_BOLD  "\e[1m"
# define COLOR_OFF   "\e[m"
# define TESHNO PURPLE COLOR_BOLD "teshno-1.0$ " COLOR_OFF RESET

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <stdbool.h>
# include <errno.h>
# include <signal.h>

int		exit_status; // to store different error codes

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
	COMMAND,
	GENERAL,
	FILE_NAME
};

enum e_ERROR_TYPE
{
	SUCCESS,
	SYNTAX_ERR
};

enum e_file
{
	in,
	out
};

typedef struct s_token
{
	char			*name;
	int				end;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_files
{
	char	*file_name;
	int		index;
}	t_files;

typedef struct s_cmd
{
		int		nbr_of_args;
		char	**cmd_args;
		// char	**files_out;
		// char	**files_in;
}	t_cmd;

// Describes a complete command with the multiple pipes if any
typedef struct s_cmd_line
{
	int		nbr_of_cmds;
	t_cmd	*cmds;
}	t_cmd_line;

typedef struct s_data
{
	char	*input;
	t_token	*tokens;
	t_cmd_line *cmd_line;
}	t_data;

int		ft_init_teshno(t_data *data);

/* ************************************************************************** */
/* LEXER																	  */
/* ************************************************************************** */
int		ft_lexer(t_data *data);
bool	ft_is_space(char c);
int		ft_get_chartype(char *s, int *i);
void	ft_handle_squote(t_data *data, int *i, int type);
void	ft_handle_dquote(t_data *data, int *i, int type);

/* ************************************************************************** */
/* UTILS																	  */
/* ************************************************************************** */

/* LIBFTLIKE */
t_token	*ms_lstlast(t_token *lst);
void	ms_lstadd_back(t_token **lst, t_token *new);
t_token	*ms_lstnew(t_token **lst);
void	ms_print_list(t_token **lst);
t_token	*ms_lstfirst(t_token **lst);
void	ms_lst_clear(t_token **lst);

/* ERRORS */
void	ft_err_msg(char *token);

/* ************************************************************************** */
/* PARSER																	  */
/* ************************************************************************** */
int		ft_parser(t_data *data);

#endif