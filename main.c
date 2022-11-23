/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:36:04 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/23 18:34:59 by rkoop            ###   ########.fr       */
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
	ft_get_env(env, &data);
	ft_init_teshno(&data);
	// system("leaks minishell");
	return (exit_status);
}
