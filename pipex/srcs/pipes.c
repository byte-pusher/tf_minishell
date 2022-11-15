/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 15:24:08 by gjupy             #+#    #+#             */
/*   Updated: 2022/08/19 17:16:23 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	alloc_pipes_arr(t_pipex *pipex)
{
	int	i;

	i = -1;
	pipex->nbr_of_pipes = pipex->childs - 1;
	pipex->pipes = malloc(sizeof(int *) * pipex->nbr_of_pipes);
	if (pipex->pipes == NULL)
		malloc_err();
	while (++i < pipex->nbr_of_pipes)
	{
		pipex->pipes[i] = malloc(sizeof(int) * 2);
		if (pipex->pipes[i] == NULL)
		{
			free_pipes(&pipex->pipes, i);
			malloc_err();
		}
	}
}

void	create_pipes_arr(t_pipex *pipex)
{
	int	i;

	i = -1;
	alloc_pipes_arr(pipex);
	while (++i < pipex->nbr_of_pipes)
	{
		if (pipe(pipex->pipes[i]) == -1)
		{
			free_pipes(&pipex->pipes, pipex->nbr_of_pipes - 1);
			err("failed to create pipe");
		}
	}
}

int	close_pipes(t_pipex *pipex, int child_nbr)
{
	int	i;
	int	rt_status;

	i = 0;
	rt_status = EXIT_SUCCESS;
	while (i < (pipex->childs - 1))
	{
		if (i != child_nbr)
		{
			rt_status = close(pipex->pipes[i][1]);
			pipex->pipes[i][1] = 0;
		}
		if (i != child_nbr - 1)
		{
			rt_status = close(pipex->pipes[i][0]);
			pipex->pipes[i][0] = 0;
		}
		i++;
	}
	return (rt_status);
}

void	free_pipes(int ***arr, int len)
{
	while (len >= 0)
	{
		free((*arr)[len]);
		len--;
	}
	free(*arr);
}
