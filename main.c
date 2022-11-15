/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:36:04 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/15 13:23:12 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/shell.h"

void	signal_handler(int signum, siginfo_t *processinfo, void *context)
{
	(void) processinfo;
	(void) context;
	// ◦ ctrl-C displays a new prompt on a new line.
	if (signum == SIGINT)
	{
		printf("\n");
		readline(TESHNO);
	}
	// ◦ ctrl-\ does nothing.
	else if (signum == SIGQUIT)
	{
		//ft_printf("\n sig ctrl +  handled.");
	}
	// ◦ ctrl-D exits the shell.
// no signal, sends EOF. detect it in line and exit
	return ;
}



int	main(int argc, char **argv, char **env)
{
	t_data	data;
	struct sigaction handling;

	(void) argc;
	(void) argv;
	(void) env; //erstmal (void). danach muss env ja benutzt werden
	//singal handling
	handling.sa_sigaction = signal_handler;
	sigaction(SIGINT, &handling, NULL);
	sigaction(SIGQUIT, &handling, NULL);
	exit_status = SUCCESS;
	ft_init_teshno(&data);
	return (EXIT_SUCCESS);
}
