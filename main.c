/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:36:04 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/22 15:40:08 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/shell.h"


int	main(int argc, char **argv, char **env)
{
	t_data	data;
	
	
	(void) argc;
	(void) argv;
	data.env_tesh = NULL;
	exit_status = SUCCESS;
    connect_signals();
	ft_get_env(env, data.env_tesh);
	ft_init_teshno(&data);
	// system("leaks minishell");
	return (exit_status);
}
