/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   route_stdout.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:32:23 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/28 13:48:01 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void		ft_route_stdout(t_cmd_table *cmd_table, t_exec *exec)
{
	if (cmd_table->next == NULL)
	{
		dup2(exec->stout, STDOUT_FILENO);
		close(exec->stout);
	}
	else
	{
		dup2(exec->end[WRITE], STDOUT_FILENO);
		close(exec->end[WRITE]);
	}
}
