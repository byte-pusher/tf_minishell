/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   route_stdout.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:32:23 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/26 16:52:24 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void		ft_route_stdout(t_cmd_table *cmd_table, t_exec *exec)
{
	dup2(exec->end[WRITE], STDOUT_FILENO);
	close(exec->end[WRITE]);
}
