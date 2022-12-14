/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 23:53:51 by gjupy             #+#    #+#             */
/*   Updated: 2022/12/14 12:49:49 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	return ;
}

void	signal_handler_inside(int signum)
{
	if (signum == SIGINT)
	{
		g_exit_status = 1;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		return ;
	}
}

void	signal_handler_silence(int signum)
{
	if (signum == SIGINT)
		return ;
}

void	ft_connect_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_change_signals(void)
{
	signal(SIGINT, signal_handler_inside);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_silence_signals(void)
{
	signal(SIGINT, signal_handler_silence);
	signal(SIGQUIT, SIG_IGN);
}
