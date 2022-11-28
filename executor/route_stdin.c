/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   route_stdin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:32:00 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/28 19:02:26 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	ft_route_stdin(t_cmd_table *cmd_table, t_exec *exec)
{
	if (cmd_table->is_redir == true && ft_is_infile(&cmd_table->redir) == true)
	{
		exec->fdin = ft_open_infiles(cmd_table->redir);
		if (exit_status != OPEN_FILE_ERR)
		{
			dup2(exec->fdin, STDIN_FILENO);
			// close(exec->fdin);
			ft_close_infiles(cmd_table);
		}
	}
	else if (cmd_table->prev != NULL)
	{
		dup2(exec->tmp_fd, STDIN_FILENO);
		close(exec->tmp_fd);
	}
}
