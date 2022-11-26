/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   route_stdin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:32:00 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/26 16:52:58 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void		ft_route_stdin(t_cmd_table *cmd_table, t_exec *exec)
{
	dup2(exec->end[READ], STDIN_FILENO);
	close(exec->end[READ]);
}
