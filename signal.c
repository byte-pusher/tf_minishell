/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 20:34:50 by rkoop             #+#    #+#             */
/*   Updated: 2022/12/12 20:35:26 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

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
