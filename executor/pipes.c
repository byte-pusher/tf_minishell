/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 15:24:08 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/25 13:43:30 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	ft_close_pipes(t_exec *exec, int child_nbr)
{
	int	i;

	i = -1;
	exit_status = EXIT_SUCCESS;
	while (++i < exec->nbr_of_pipes)
	{
		if (i != child_nbr)
		{
			exit_status = close(exec->pipes[i][1]);
			exec->pipes[i][1] = 0;
		}
		if (i != child_nbr - 1)
		{
			exit_status = close(exec->pipes[i][0]);
			exec->pipes[i][0] = 0;
		}
	}
}
