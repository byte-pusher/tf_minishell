/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:36:04 by gjupy             #+#    #+#             */
/*   Updated: 2022/12/09 15:05:31 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/shell.h"

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void) argc;
	(void) argv;
	data.env_tesh = NULL;
	g_exit_status = SUCCESS;
	connect_signals();
	data.env_exists = true;
	ft_get_env(env, &data);
	ft_init_teshno(&data);
	exit(g_exit_status);
}
