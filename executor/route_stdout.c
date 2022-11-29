/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   route_stdout.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:32:23 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/29 21:15:16 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void		ft_route_stdout(t_cmd_table *cmd_table, t_exec *exec)
{
	if (cmd_table->is_redir == true
			&& ft_is_outfile(&cmd_table->redir) == true)
	{
		exec->fdout = ft_open_outfiles(cmd_table->redir);
		if (exit_status != OPEN_FILE_ERR)
		{
			dup2(exec->fdout, STDOUT_FILENO);
			ft_close_outfiles(cmd_table);
		}
	}
	else if (cmd_table->next == NULL)
	{
		// if (ft_is_heredoc(&cmd_table->redir) == true)
		// {
		// 	dup2(exec->stout, exec->here_fd[WRITE]);
		// 	close(exec->stout);
		// }
		dup2(exec->stout, STDOUT_FILENO);
		close(exec->stout);
	}
	else
	{
		// if (ft_is_heredoc(&cmd_table->redir) == true)
		// {
		// 	dup2(exec->end[READ], exec->here_fd[WRITE]);
		// 	close(exec->end[READ]);
		// }
		dup2(exec->end[WRITE], STDOUT_FILENO);
		close(exec->end[WRITE]);
	}
}
