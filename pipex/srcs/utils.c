/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 18:49:06 by gjupy             #+#    #+#             */
/*   Updated: 2022/08/22 10:41:06 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*
opens in or out file, depending on the file var parameter
and if there is here-doc
*/
void	open_file(char **argv, t_pipex *pipex, int file)
{
	if (file == in)
	{
		pipex->fd[0] = open(argv[1], O_RDONLY);
		if (pipex->fd[0] == -1)
			err("failed to open infile");
	}
	else if (file == out)
	{
		if (pipex->here_doc == false)
			pipex->fd[1] = open(argv[pipex->childs + 2],
					O_WRONLY | O_CREAT | O_TRUNC, 0777);
		else if (pipex->here_doc == true)
			pipex->fd[1] = open(argv[pipex->childs + 2],
					O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (pipex->fd[1] == -1)
			err("failed to open outfile");
	}
}

void	child_wait_pid(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->childs)
	{
		waitpid(pipex->pids[i], &pipex->status, 0);
		i++;
	}
	pipex->status = pipex->status >> 8;
	pipex->status = pipex->status & 0x000000ff;
}
