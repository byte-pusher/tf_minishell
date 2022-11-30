/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   route_stdout_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:44:57 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/30 21:41:34 by gjupy            ###   ########.fr       */
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

static void	ft_open (t_redir *redir, int *ret)
{
	// redir->fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (redir->type == GREAT)
		(*ret) = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (redir->type == GREATGREAT)
		(*ret) = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0777);
}

int	ft_open_outfiles(t_redir *redir)
{
	int		ret;
	t_redir	*current;

	current = ft_lstfirst_rd(&redir);
	while (current != NULL)
	{
		ft_open(current, &ret);
		if (ret == -1)
		{
			ft_close_outfiles_err(current->prev);
			g_exit_status = OPEN_FILE_ERR;
			ft_err_msg(current->file);
			return (ret);
		}
		current = current->next;
	}
	return (ret);
}
