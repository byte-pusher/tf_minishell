/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:36:04 by gjupy             #+#    #+#             */
/*   Updated: 2022/12/12 23:55:30 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void) argc;
	(void) argv;
	data.env_tesh = NULL;
	connect_signals();
	data.env_exists = true;
	ft_get_env(env, &data);
	ft_init_teshno(&data);
	exit(g_exit_status);
}
