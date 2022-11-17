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

void	signal_handler(int signum, siginfo_t *processinfo, void *context)
{
	(void) processinfo;
	(void) context;
	// ◦ ctrl-C displays a new prompt on a new line.
	
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
    	//rl_replace_line("", 0);
    	rl_redisplay();
		
	}
	// ◦ ctrl-\ does nothing.
	else if (signum == SIGQUIT)
	{
		write(1, "  \b\b", 4);
		ft_printf("\n sig ctrl +  handled.");
	}
	// ◦ ctrl-D exits the shell.
	// no signal, sends EOF to stdin. detect it in lexer and exit
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
