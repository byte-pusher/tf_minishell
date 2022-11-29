/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   route_stdin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:32:00 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/29 19:59:02 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	ft_route_stdin(t_cmd_table *cmd_table, t_exec *exec)
{
	// test also ls nonexistentfile | <<1
	if (cmd_table->is_redir == true && ft_is_heredoc(&cmd_table->redir) == true)
		ft_heredoc(cmd_table->redir, exec);
	if (cmd_table->is_redir == true && ft_is_infile(&cmd_table->redir) == true)
	{
		exec->fdin = ft_open_infiles(cmd_table->redir);
		if (exit_status != OPEN_FILE_ERR)
		{
			if (ft_heredoc_after_infile(cmd_table->redir) == false)
			{
				dup2(exec->fdin, STDIN_FILENO);
				ft_close_infiles(cmd_table);
				return ;
			}
			ft_close_infiles(cmd_table);
		}
	}
	dup2(exec->tmp_fd, STDIN_FILENO);
	close(exec->tmp_fd);
}
