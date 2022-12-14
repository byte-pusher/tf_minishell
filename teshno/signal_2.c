/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:58:02 by gjupy             #+#    #+#             */
/*   Updated: 2022/12/14 12:58:39 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

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
