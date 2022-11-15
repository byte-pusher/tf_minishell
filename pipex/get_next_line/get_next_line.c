/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 07:57:36 by nikito            #+#    #+#             */
/*   Updated: 2022/08/10 23:26:08 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list_gnl	*stash = NULL;
	char				*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (NULL);
	line = NULL;
	read_and_stash(fd, &stash);
	if (stash == NULL)
		return (NULL);
	extract_line(stash, &line);
	clean_stash(&stash);
	if (line && line[0] == '\0')
	{
		free_stash(stash);
		stash = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

void	read_and_stash(int fd, t_list_gnl **stash)
{
	char	*buff;
	int		bytes_read;

	bytes_read = 1;
	while (!found_new_line(*stash) && bytes_read != 0)
	{
		buff = malloc(BUFFER_SIZE + 1);
		if (buff == NULL)
			return ;
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if ((*stash == NULL && bytes_read == 0) || bytes_read == -1)
		{
			free(buff);
			return ;
		}
		buff[bytes_read] = '\0';
		add_to_stash(stash, buff, bytes_read);
		free(buff);
	}
}

void	add_to_stash(t_list_gnl **stash, char *buff, int bytes_read)
{
	int			i;
	t_list_gnl	*last;
	t_list_gnl	*new_node;

	new_node = malloc(sizeof(t_list_gnl));
	if (new_node == NULL)
		return ;
	new_node->next = NULL;
	new_node->content = malloc(bytes_read + 1);
	if (new_node->content == NULL)
		return ;
	i = 0;
	while (buff[i] && i < bytes_read)
	{
		new_node->content[i] = buff[i];
		i++;
	}
	new_node->content[i] = '\0';
	if (*stash == NULL)
	{
		*stash = new_node;
		return ;
	}
	last = lst_get_last(*stash);
	last->next = new_node;
}

void	extract_line(t_list_gnl *stash, char **line)
{
	int	i;
	int	j;

	if (stash == NULL)
		return ;
	generate_line(line, stash);
	if (*line == NULL)
		return ;
	j = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				(*line)[j++] = stash->content[i];
				break ;
			}
			(*line)[j++] = stash->content[i++];
		}
		stash = stash->next;
	}
	(*line)[j] = '\0';
}

void	clean_stash(t_list_gnl **stash)
{
	t_list_gnl	*last;
	t_list_gnl	*clean_node;
	int			i;
	int			j;

	clean_node = malloc(sizeof(t_list_gnl));
	if (stash == NULL || clean_node == NULL)
		return ;
	clean_node->next = NULL;
	last = lst_get_last(*stash);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content && last->content[i] == '\n')
		i++;
	clean_node->content = malloc((ft_strlen(last->content) - i) + 1);
	if (clean_node->content == NULL)
		return ;
	j = 0;
	while (last->content[i])
		clean_node->content[j++] = last->content[i++];
	clean_node->content[j] = '\0';
	free_stash(*stash);
	*stash = clean_node;
}
