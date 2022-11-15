/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 18:17:41 by gjupy             #+#    #+#             */
/*   Updated: 2022/08/12 21:19:57 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	pipex.childs = argc - 3;
	input_err_check(&pipex, argc, argv);
	create_child_prcs(&pipex, argv, env);
	child_wait_pid(&pipex);
	free(pipex.pids);
	exit(pipex.status);
}
