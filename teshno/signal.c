/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 23:53:51 by gjupy             #+#    #+#             */
/*   Updated: 2022/12/12 23:55:26 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		rl_redisplay();
		write(2, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}

void	connect_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
