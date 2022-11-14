/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 12:58:32 by rkoop             #+#    #+#             */
/*   Updated: 2022/08/04 16:23:02 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static void	ft_init_box(t_hold *box)
{
	box->line = NULL;
	box->rem_str = NULL;
	box->bytes_count = 1;
}

static void	*ft_guard(void *ptr, char *tmp, char *line)
{
	if (ptr == NULL)
		return (ft_release(tmp, line));
	return (ptr);
}

static char	*ft_read(int fd, char *line, t_hold *box)
{
	char		*tmp;
	char		*cur_line;
	ssize_t		linelen;
	ssize_t		cur_linelen;	

	tmp = malloc(sizeof(char) * BUFFER_SIZE);
	if (tmp == NULL)
		return (ft_release(tmp, line));
	box->bytes_count = read(fd, tmp, BUFFER_SIZE);
	if (box->bytes_count == -1)
		return (ft_release(tmp, line));
	linelen = ft_strlen_gnl(line);
	cur_linelen = linelen + box->bytes_count;
	cur_line = ft_guard(malloc(sizeof(char) * cur_linelen + 1), tmp, line);
	if (cur_line == NULL)
		return (NULL);
	ft_strncpy(cur_line, line, linelen);
	ft_strncpy(cur_line + linelen, tmp, box->bytes_count);
	ft_release(tmp, line);
	return (cur_line);
}

static void	ft_save(char *line, t_hold *box)
{
	int	cur_linelen;
	int	rem_linelen;

	cur_linelen = ft_strlen_nl(line);
	if (!cur_linelen)
		return ;
	box->line = malloc(cur_linelen + 1);
	if (box->line == NULL)
		return ;
	ft_strncpy(box->line, line, cur_linelen);
	rem_linelen = ft_strlen_gnl(line) - cur_linelen;
	box->rem_str = malloc(rem_linelen + 1);
	if (box->rem_str == NULL)
	{
		free(box->line);
		box->line = NULL;
		return ;
	}
	ft_strncpy(box->rem_str, line + cur_linelen, rem_linelen);
}

char	*get_next_line(int fd)
{
	static char	*line;
	t_hold		box;

	if (BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
		return (NULL);
	ft_init_box(&box);
	if (line == NULL)
		line = ft_read(fd, line, &box);
	while (line != NULL && check_nl(line) == 0 && box.bytes_count > 0)
		line = ft_read(fd, line, &box);
	if (line == NULL)
		return (NULL);
	ft_save(line, &box);
	free(line);
	line = box.rem_str;
	return (box.line);
}
