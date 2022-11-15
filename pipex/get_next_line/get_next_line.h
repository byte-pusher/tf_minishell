/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 21:02:51 by gjupy             #+#    #+#             */
/*   Updated: 2022/08/10 22:38:17 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "../includes/pipex.h"
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct s_list_gnl
{
	char				*content;
	struct s_list_gnl	*next;
}				t_list_gnl;

char		*get_next_line(int fd);
int			found_new_line(t_list_gnl *stash);
t_list_gnl	*lst_get_last(t_list_gnl *stash);
void		read_and_stash(int fd, t_list_gnl **stash);
void		add_to_stash(t_list_gnl **stash, char *buf, int readed);
void		extract_line(t_list_gnl *stash, char **line);
void		generate_line(char **line, t_list_gnl *stash);
void		clean_stash(t_list_gnl **stash);
int			ft_strlen(const char *str);
void		free_stash(t_list_gnl *stash);
#endif