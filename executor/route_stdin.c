/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   route_stdin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:32:00 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/28 12:46:18 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void		ft_route_stdin(t_cmd_table *cmd_table, t_exec *exec)
{
	if (cmd_table->prev != NULL)
	{
		dup2(exec->tmp_fd, STDIN_FILENO);
		close(exec->tmp_fd);
	}
}
