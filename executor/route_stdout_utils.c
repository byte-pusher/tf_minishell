/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   route_stdout_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:44:57 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/30 18:17:17 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

bool	ft_is_outfile(t_redir **redir)
{
	t_redir	*current;

	current = *redir;
	while (current != NULL)
	{
		if (current->type == GREAT || current->type == GREATGREAT)
			return (true);
		current = current->next;
	}
	return (false);
}

void	ft_close_outfiles_err(t_redir *redir)
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

void	ft_close_outfiles(t_cmd_table *cmd_table)
{
	t_redir	*current;

	current = ft_lstfirst_rd(&cmd_table->redir);
	while (current != NULL)
	{
		if (current->type == GREAT || current->type == GREATGREAT)
			close(current->fd);
		current = current->next;
	}
}

int	ft_open_outfiles(t_redir *redir)
{
	int		ret;
	t_redir *current;

	current = ft_lstfirst_rd(&redir);
	while (current != NULL)
	{
		if (current->type == GREAT) // out
		{
			current->fd = open(current->file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
			ret = current->fd;
		}
		else if (current->type == GREATGREAT)
		{
			current->fd = open(current->file, O_WRONLY | O_CREAT | O_APPEND, 0777);
			ret = current->fd;
		}
		if (current->fd == -1)
		{
			ft_close_outfiles_err(current->prev);
			exit_status = OPEN_FILE_ERR;
			ft_err_msg(current->file);
			return (ret);
		}
		current = current->next;
	}
	return (ret);
}
