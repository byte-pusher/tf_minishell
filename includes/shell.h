/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:36:57 by gjupy             #+#    #+#             */
/*   Updated: 2022/12/14 16:12:48 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# define PURPLE "\033[0;35m"
# define RESET "\033[0m"
# define COLOR_BOLD  "\e[1m"
# define COLOR_OFF   "\e[m"

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
# include <sys/wait.h>
# include <sys/ioctl.h>

/* ************************************************************************** */
/* READLINE MISSING PROTOTYPES												  */
/* ************************************************************************** */
void		rl_replace_line(const char *text, int clear_undo);
extern void	rl_clear_history(void);

int			g_exit_status;

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
	SUCCESS = 0,
	OPEN_FILE_ERR = 1,
	ARG_REQ = 2,
	IS_DIR = 126,
	CMD_NOT_FOUND = 127,
	NON_NUM_ARG = 255,
	SYNTAX_ERR = 258,
	INVALID_IDENTIFIER = 257,
	ABORT
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

enum e_STATUS
{
	DOUBLE_OPEN,
	DOUBLE_CLOSED,
	SINGLE_OPEN,
	SINGLE_CLOSED,
	OPEN,
	NON
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
	bool			mixed_quotes;
	char			*name;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_redir
{
	int				type;
	int				fd;
	int				here_tmp_fd;
	char			*file;
	struct s_redir	*head;
	struct s_redir	*next;
	struct s_redir	*prev;
}	t_redir;

typedef struct s_cmd_table
{
	int					builtin_type;
	int					here_tmp_fd;
	char				**cmd_args;
	char				*path_name;
	bool				is_command;
	bool				cmd_not_found;
	bool				is_redir;
	bool				is_builtin;
	bool				expander_delimiter;
	bool				mixed_quotes;
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
	struct s_env	*prev;
}	t_env;

typedef struct s_exec
{
	int	end[2];
	int	here_fd[2];
	int	nbr_of_pipes;
	int	tmp_fd;
	int	stin;
	int	stout;
	int	fdin;
	int	fdout;
	int	file_fd;
	int	cmd_count;
	int	no_rights;
	int	pid;
	int	i;
}			t_exec;

typedef struct s_data
{
	char		*input;
	char		*in;
	int			prev_exit_code;
	bool		env_exists;
	bool		exit_shell;
	bool		empty_input;
	bool		unclosed_quotes;
	t_exec		*exec;
	t_env		*env_tesh;
	t_token		*tokens;
	t_cmd_table	*cmd_table;
}	t_data;

typedef struct s_heredoc
{
	char	*read;
	bool	is_read_var;
}	t_heredoc;

void		ft_init_teshno(t_data *data);
void		ft_get_env(char **env, t_data *data);
void		print_env(t_env **lst, t_data *data);
bool		ft_is_empty(char *input);

/* ************************************************************************** */
/* FREE																		  */
/* ************************************************************************** */
void		ft_free_all(t_data *data);
void		ft_free_strings(char ***s);

/* ************************************************************************** */
/* LEXER																	  */
/* ************************************************************************** */
void		ft_lexer(t_data *data);
char		*get_var(t_data *data, char *var);
int			get_var_len(char *env_var);
void		ft_str_remove(char *str, const char *sub);
int			get_var_amount(char *token_name);
void		free_var_arr(char **var_arr);

/* UTILS */
bool		ft_is_space(char c);
bool		ft_is_redir_token(char c);
int			ft_get_chartype(char *s, int *i);
bool		ft_is_file_name(t_token *new_token);
void		ft_cpy_string(t_data *data, t_token *new_token, int *i);

/* ************************************************************************** */
/* EXPANSION																  */
/* ************************************************************************** */
void		expansion(t_data *data);

/* UTILS */
bool		ft_is_double_dollar(char *s);
int			ft_get_next_var(char *s);
void		ft_insert_dollars(char *s);

/* ************************************************************************** */
/* UTILS																	  */
/* ************************************************************************** */
/* SIGNALS*/
void		ft_connect_signals(void);
void		ft_change_signals(void);
void		ft_silence_signals(void);

void		signal_handler(int signum);
void		signal_handler_inside(int signum);
void		signal_handler_silence(int signum);

/* LST */
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

t_env		*ft_lstlast_env(t_env *lst);
void		ft_lstadd_back_env(t_env **lst, t_env *new);
t_env		*ft_lstnew_env(void);
t_env		*ft_lstfirst_env(t_env **lst);
void		ft_lstclear_env(t_env **lst);
int			ft_lstsize_env(t_env **lst);
void		ft_lstdel_env(t_data *data, t_env *node);

/* ERRORS */
void		ft_err_msg(char *s);
bool		ft_is_path_cmd(char *s);
void		ft_err_exit(char *s, int e_status, t_data *data);

/* ************************************************************************** */
/* PARSER																	  */
/* ************************************************************************** */
void		ft_parser(t_data *data);

/* UTILS */
bool		ft_is_redir(int type);
void		ft_create_cmd_table_lst(t_data *data);
void		print_cmd_strings(t_cmd_table *cmd_table); // danach löschen
bool		ft_check_redir_err(t_token *token);
int			get_combined_len(t_token *current_token);
bool		ft_is_cmd_or_quotes(t_token *token);

bool		ft_check_quotes(char *str);
bool		ft_check_pipe_sequence(t_token *token);
bool		ft_check_others(t_token **token);

/* CMD_PARSER */
void		ft_command_parser(t_cmd_table *cmd_table, t_token **token,
				t_data *data);
void		ft_create_cmd_args(t_cmd_table *cmd_table, t_token **token);

/* REDIR_PARSER*/
void		ft_redir_parser(t_cmd_table *cmd_table, t_token **token);

/* ************************************************************************** */
/* BUILTIN																	  */
/* ************************************************************************** */
bool		ft_is_builtin(t_cmd_table *cmd_table, char *builtin);
void		ft_exit(char **arg, t_cmd_table *cmd_table, t_data *data);
void		ft_env(t_env *env_tesh);
void		ft_echo(char **cmd_args);
void		ft_export(char **cmd_args, t_env *env_tesh, t_data *data);
void		ft_unset(char **cmd_args, t_env *env_tesh, t_data *data);
void		ft_cd(char **cmd_args, t_env *env_tesh, t_data *data);
void		ft_pwd(void);
int			is_var_declaration(char *cmd_arg);
int			comp_var_len(char *cmd_arg);
int			valid_export(char *cmd_arg);
int			var_exists(char *cmd_arg, t_env *env_tesh, t_data *data);
int			var_exists_del(char *cmd_arg, t_env *env_tesh, t_data *data);
int			is_var_declaration(char *cmd_arg);
int			valid_export(char *cmd_arg);
int			get_nr_of_vars(char *token_name);
char		*get_dir(t_env *env_tesh, char *var);
void		set_pwd(t_env *env_tesh, t_data *data);
void		set_oldpwd(t_env *env_tesh, t_data *data, char *tmp_dir);
t_env		*ft_set_head(t_env *env_tesh);
char		*get_value(t_data *data, char *var, bool *is_env_var);
void		insert_value(t_token *token, char *var, char *value, int start);
void		change_token_name(t_data *data, t_token *token, int start, int end);

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
void		ft_end_prcs(t_exec *exec);
void		ft_close_open_fds(t_exec *exec, t_cmd_table **cmd_table);

/* ROUTES */
void		ft_route_stdin(t_cmd_table *cmd_table, t_exec *exec);
void		ft_close_infiles(t_cmd_table *cmd_table);
bool		ft_is_infile(t_redir **redir);
int			ft_open_infiles(t_redir *redir);

void		ft_route_stdout(t_cmd_table *cmd_table, t_exec *exec);
void		ft_close_outfiles(t_cmd_table *cmd_table);
int			ft_open_outfiles(t_redir *redir);
bool		ft_is_outfile(t_redir **redir);

void		ft_heredoc(t_exec *exec, t_cmd_table *cmd_table, t_data *data);
bool		ft_is_heredoc(t_redir **redir);
bool		ft_heredoc_after_infile(t_redir *redir);
void		ft_open_heredocs(t_exec *exec, t_cmd_table **cmd_table,
				t_data *data);
void		ft_expand_read(t_heredoc *heredoc, t_data *data);
bool		ft_is_var(char *s);

#endif
