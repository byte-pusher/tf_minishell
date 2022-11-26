/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:36:57 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/26 16:31:40 by gjupy            ###   ########.fr       */
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


/* ************************************************************************** */
/* READLINE MISSING PROTOTYPES												  */
/* ************************************************************************** */
void 		rl_replace_line(const char *text, int clear_undo);
extern void rl_clear_history (void);

int			exit_status; // to store different error codes

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
	OPEN_FILE_ERR,
	CMD_NOT_FOUND,
	ABORT,
	PIPE_ERR
};

enum e_BUILTIN_TYPE
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
};

enum e_PIPE_END
{
	READ,
	WRITE
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
	int					builtin_type;
	char				**cmd_args;
	char				*path_name;
	bool				is_command;
	bool				is_redir;
	bool				is_builtin;
	pid_t				pid;
	t_redir				*redir;
	struct s_cmd_table	*next;
	struct s_cmd_table	*prev;
}	t_cmd_table;

typedef struct s_env
{
	char			*var;
	bool			hidden;
	struct s_env	*next;
}	t_env;

typedef struct s_exec
{
	int	end[2];
	int	here_fd[2];
	int	nbr_of_pipes;
	int	tmp_fd;
	int	stin;
	int	stout;
	int	file_fd;
	int	cmd_count;
	int	no_rights;
	int	pid;
	int	i;
}			t_exec;

typedef struct s_data
{
	char		*input;
	t_exec		*exec;
	t_env		*env_tesh;
	t_token		*tokens;
	t_cmd_table	*cmd_table;
	// char		**ms_env;
}	t_data;

int			ft_init_teshno(t_data *data);
void		ft_get_env(char **env, t_data *data);
void		print_env(t_env **lst);

/* ************************************************************************** */
/* FREE																		  */
/* ************************************************************************** */
void		ft_free_all(t_data *data);
void		ft_free_strings(char ***s);

/* ************************************************************************** */
/* LEXER																	  */
/* ************************************************************************** */
void		ft_lexer(t_data *data);
bool		ft_is_space(char c);
int			ft_get_chartype(char *s, int *i);

/* ************************************************************************** */
/* UTILS																	  */
/* ************************************************************************** */
/* SIGNALS*/
void		connect_signals();


/* LST */
t_cmd_table	*ft_lstnew_ct(void);
t_cmd_table	*ft_lstfirst_ct(t_cmd_table **lst);
t_cmd_table	*ft_lstlast_ct(t_cmd_table *lst);
void		ft_lstclear_ct(t_cmd_table **lst);
void		ft_lstadd_back_ct(t_cmd_table **lst, t_cmd_table *new);
int			ft_lstsize_ct(t_cmd_table **lst);

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

t_env		*ft_lstlast_env(t_env *lst);
void		ft_lstadd_back_env(t_env **lst, t_env *new);
t_env		*ft_lstnew_env(void);
t_env		*ft_lstfirst_env(t_env **lst);
void		ft_lstclear_env(t_env **lst);
int			ft_lstsize_env(t_env **lst);

/* ERRORS */
void		ft_err_msg(char *s);

/* ************************************************************************** */
/* PARSER																	  */
/* ************************************************************************** */
void		ft_parser(t_data *data);

/* UTILS */
bool		ft_is_redir(int type);
void		ft_create_cmd_table_lst(t_data *data);
void		print_cmd_strings(t_cmd_table *cmd_table); // danach löschen
void		ft_check_redir_err(t_token *token);

/* CMD_PARSER */
void		ft_command_parser(t_cmd_table *cmd_table, t_token *token, t_data *data);

/* REDIR_PARSER*/
void		ft_redir_parser(t_cmd_table *cmd_table, t_token **token);

/* ************************************************************************** */
/* BUILTIN																	  */
/* ************************************************************************** */
bool		ft_is_builtin(t_cmd_table *cmd_table, char *builtin);
void		ft_exit(void);
void		ft_env(t_env *env_tesh);
void		ft_echo(char **cmd_args);

/* UTILS */
bool		ft_is_flag(char **cmd_args);
void		ft_skip_flags(char **cmd_args, int *i);

/* ************************************************************************** */
/* EXECUTOR																	  */
/* ************************************************************************** */
void		ft_executor(t_data *data);

/* UTILS */
char		**ft_get_env_arr(t_env *env_tesh);
bool		ft_check_single_builtin(t_cmd_table *cmd_table);
bool		ft_check_single_cmd(t_cmd_table *cmd_table);
t_exec		*ft_create_exec(void);

/* ROUTES */
void		ft_route_stdin(t_cmd_table *cmd_table, t_exec *exec);
void		ft_route_stdout(t_cmd_table *cmd_table, t_exec *exec);

#endif