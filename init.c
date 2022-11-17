/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:56:46 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/17 17:15:58 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/shell.h"

void	ft_init_structs(t_data *data)
{
	data->tokens = NULL;
	data->cmd_table = NULL;
	// was muss noch initialisiert werden?
}

int	ft_init_teshno(t_data *data)
{
	while (true)
	{
		ft_init_structs(data);
		data->input = readline(TESHNO);
		if (ft_strncmp(data->input, "exit", 4) == 0)
			break ;
		if (data->input[0] != '\0')
		{
			add_history(data->input);
			exit_status = ft_lexer(data);				// still need to handle malloc errors in ft_lexer
			exit_status = ft_parser(data);
		}
		ft_free_all(data);
	}
	clear_history(); // rl_clear_history verwenden
	return (exit_status);
}
