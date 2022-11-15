/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 21:57:07 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/08 13:45:07 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H


# include "../libs/libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <stdbool.h>
# include <errno.h>

enum	e_file {in, out};

typedef struct s_pipex
{
	int		fd[2];
	pid_t	*pids;
	int		childs;
	int		**pipes;
	int		nbr_of_pipes;
	int		pipe_read;
	int		pipe_write;
	int		infile;
	int		outfile;
	char	*path;
	char	**pathnames;
	char	**cmd_args;
	char	*command;
	char	*delimiter;
	int		status;
	bool	here_doc;
}	t_pipex;

/* ************************************************************************** */
/* CHILDS																	  */
/* ************************************************************************** */
void	create_child_prcs(t_pipex *pipex, char **argv, char **env);

/* ************************************************************************** */
/* PIPES																	  */
/* ************************************************************************** */
void	create_pipes_arr(t_pipex *pipex);
int		close_pipes(t_pipex *pipex, int child_nbr);
void	free_pipes(int ***arr, int len);

/* ************************************************************************** */
/* COMMANDS																  */
/* ************************************************************************** */
void	find_path_line_and_split(char **env, t_pipex *pipex);
int		get_cmd(t_pipex *pipex);

/* ************************************************************************** */
/* UTILS																      */
/* ************************************************************************** */
void	open_file(char **argv, t_pipex *pipex, int file);
void	child_wait_pid(t_pipex *pipex);

/* ************************************************************************** */
/* ERR_PARSER																  */
/* ************************************************************************** */
bool	is_space(char c);
bool	str_of_spaces(char *argv);
bool	is_here_doc(t_pipex *pipex, char **argv);
int		check_cmd_strs(char **s, t_pipex *pipex);
void	input_err_check(t_pipex *pipex, int argc, char **argv);

/* ************************************************************************** */
/* ERROR																      */
/* ************************************************************************** */
void	cmd_err(t_pipex *pipex);
void	input_err(char *msg);
void	malloc_err(void);
void	err(char *msg);

#endif