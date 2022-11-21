/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:36:04 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/21 11:27:56 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/shell.h"


int	main(int argc, char **argv, char **env)
{
	t_data	data;
	
	
	(void) argc;
	(void) argv;
	(void) env; //erstmal (void). danach muss env ja benutzt werden
	exit_status = SUCCESS;
    connect_signals();
	ft_init_teshno(&data);
	return (EXIT_SUCCESS);
}
