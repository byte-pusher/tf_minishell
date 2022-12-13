/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   route_stdout.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:32:23 by gjupy             #+#    #+#             */
/*   Updated: 2022/12/13 14:24:57 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	ft_route_stdout(t_cmd_table *cmd_table, t_exec *exec)
{
	if (cmd_table->is_redir == true
		&& ft_is_outfile(&cmd_table->redir) == true)
	{
		exec->fdout = ft_open_outfiles(cmd_table->redir);
		if (g_exit_status != OPEN_FILE_ERR)
		{
			if (dup2(exec->fdout, STDOUT_FILENO) == -1)
				ft_err_msg("dup2");
			ft_close_outfiles(cmd_table);
		}
	}
	else if (cmd_table->next == NULL)
	{
		if (dup2(exec->stout, STDOUT_FILENO) == -1)
			ft_err_msg("dup2");
		close(exec->stout);
	}
	else
	{
		if (dup2(exec->end[WRITE], STDOUT_FILENO) == -1)
			ft_err_msg("dup2");
		close(exec->end[WRITE]);
	}
}
