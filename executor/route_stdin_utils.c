/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   route_stdin_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:20:35 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/28 19:02:37 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

bool	ft_is_infile(t_redir **redir)
{
	t_redir	*current;

	current = *redir;
	while (current != NULL)
	{
		if (current->type == LESS)
			return (true);
		current = current->next;
	}
	return (false);
}

void	ft_close_infiles_err(t_redir *redir)
{
	t_redir	*current;

	current = redir;
	while (current != NULL)
	{
		if (current->type == LESS)
			close(current->fd);
		current = current->prev;
	}
}

void	ft_close_infiles(t_cmd_table *cmd_table)
{
	t_redir	*current;

	current = ft_lstfirst_rd(&cmd_table->redir);
	while (current != NULL)
	{
		if (current->type == LESS)
			close(current->fd);
		current = current->next;
	}
}

int	ft_open_infiles(t_redir *redir)
{
	int		ret;
	t_redir *current;

	current = ft_lstfirst_rd(&redir);
	while (current != NULL)
	{
		if (current->type == LESS) // in
		{
			current->fd = open(current->file, O_RDONLY);
			ret = current->fd;
		}
		if (current->fd == -1)
		{
			ft_close_infiles_err(current->prev);
			exit_status = OPEN_FILE_ERR;
			ft_err_msg(current->file);
		}
		current = current->next;
	}
	return (ret);
}
