/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:56:46 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/15 15:50:41 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/shell.h"

int	ft_init_teshno(t_data *data)
{
	data->tokens = NULL;	// extra fct zum initialisieren implementieren
	data->cmd_line = NULL;

	while (true)
	{
		data->input = readline(TESHNO);
		if (data->input[0] != '\0')
		{
			add_history(data->input);
			ft_lexer(data);				// still need to handle malloc errors in ft_lexer
			exit_status = ft_parser(data);
		}
	}
	clear_history(); // rl_clear_history verwenden
}
