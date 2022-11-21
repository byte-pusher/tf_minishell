/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:36:57 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/21 18:42:39 by gjupy            ###   ########.fr       */
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
	SYNTAX_ERR,
	MALLOC_ERR,
	OPEN_FILE_ERR,
	CMD_NOT_FOUND
};

enum e_file
{
	in,
	out
};

typedef struct s_token
{
	int				end;
	int				type;
	char			*name;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_redir
{
	int				type;
	int				fd;
	char			*file;
	struct s_redir	*head;
	struct s_redir	*next;
	struct s_redir	*prev;
}	t_redir;

typedef struct s_cmd_table
{
		char				**cmd_args;
		bool				is_command;
		bool				is_redir;
		t_redir				*redir;
		struct s_cmd_table	*next;
		struct s_cmd_table	*prev;
}	t_cmd_table;

typedef struct s_data
{
	char		*input;
	int			nbr_of_cmds;
	t_token		*tokens;
	t_cmd_table	*cmd_table;
	// char		**ms_env;
}	t_data;

int		ft_init_teshno(t_data *data);

/* ************************************************************************** */
/* FREE																		  */
/* ************************************************************************** */
void	ft_free_all(t_data *data);

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

/* LIBFTLIKE */
t_cmd_table	*ft_lstnew_ct(void);
t_cmd_table	*ft_lstfirst_ct(t_cmd_table **lst);
t_cmd_table	*ft_lstlast_ct(t_cmd_table *lst);
void		ft_lstclear_ct(t_cmd_table **lst);
void		ft_lstadd_back_ct(t_cmd_table **lst, t_cmd_table *new);

t_token		*ft_lstlast_t(t_token *lst);
void		ft_lstadd_back_t(t_token **lst, t_token *new);
t_token		*ft_lstnew_t(void);
void		ms_print_list(t_token **lst);
t_token		*ft_lstfirst_t(t_token **lst);
void		ft_lst_clear_t(t_token **lst);

t_redir		*ft_lstlast_rd(t_redir *lst);
void		ft_lstadd_back_rd(t_redir **lst, t_redir *new);
t_redir		*ft_lstnew_rd(void);
t_redir		*ft_lstfirst_rd(t_redir **lst);
void		ft_lstclear_rd(t_redir **lst);

/* ERRORS */
void	ft_err_msg(char *s);
void	ft_check_redir_err(t_token *token);

/* ************************************************************************** */
/* PARSER																	  */
/* ************************************************************************** */
void		ft_parser(t_data *data);

/* UTILS */
bool	ft_is_redir(int type);
void	ft_create_cmd_table_lst(t_data *data);
void	print_cmd_strings(t_cmd_table *cmd_table); // danach löschen

/* CMD_PARSER */
void	ft_command_parser(t_cmd_table *cmd_table, t_token *token);

/* REDIR_PARSER*/
void	ft_redir_parser(t_cmd_table *cmd_table, t_token **token);

#endif