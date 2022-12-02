/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   route_stdin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:32:00 by gjupy             #+#    #+#             */
/*   Updated: 2022/12/01 14:51:02 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	ft_route_filein(t_cmd_table *cmd_table, t_exec *exec)
{
	if (dup2(exec->fdin, STDIN_FILENO) == -1)
		ft_err_msg("dup2");
	ft_close_infiles(cmd_table);
}

void	ft_route_heredoc(t_cmd_table *cmd_table, t_exec *exec)
{
	if (dup2(cmd_table->here_tmp_fd, exec->tmp_fd) == -1)
		ft_err_msg("dup2");
}

void	ft_route_stdin(t_cmd_table *cmd_table, t_exec *exec)
{
	if (cmd_table->is_redir == true && ft_is_heredoc(&cmd_table->redir) == true)
	{
		if (ft_heredoc_after_infile(cmd_table->redir) == true)
			ft_route_heredoc(cmd_table, exec);
		close(cmd_table->here_tmp_fd);
	}
	if (cmd_table->is_redir == true && ft_is_infile(&cmd_table->redir) == true)
	{
		exec->fdin = ft_open_infiles(cmd_table->redir);
		if (g_exit_status != OPEN_FILE_ERR)
		{
			if (ft_heredoc_after_infile(cmd_table->redir) == false)
			{
				ft_route_filein(cmd_table, exec);
				return ;
			}
			ft_close_infiles(cmd_table);
		}
	}
	if (dup2(exec->tmp_fd, STDIN_FILENO) == -1)
		ft_err_msg("dup2");
	close(exec->tmp_fd);
}
