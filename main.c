/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:36:04 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/17 17:53:25 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/shell.h"
# include <readline/readline.h>
# include <readline/history.h>





int	main(int argc, char **argv, char **env)
{
	t_data	data;
	
	(void) argc;
	(void) argv;
	(void) env; //erstmal (void). danach muss env ja benutzt werden
	exit_status = SUCCESS;
	ft_init_teshno(&data);
	return (EXIT_SUCCESS);
}
