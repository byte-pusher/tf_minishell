/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:56:46 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/21 15:12:59 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/shell.h"

int	ft_init_teshno(t_data *data)
{
	data->tokens = NULL;	// extra fct zum initialisieren implementieren
	data->cmd_table = NULL;

	while (true)
	{
		data->input = readline(TESHNO);
		if (data->input  == NULL)
			exit_status = ABORT;
		if (data->input[0] != '\0' && data->input[0] != EOF)
		{
			add_history(data->input);
			ft_lexer(data);
			// still need to handle malloc errors in ft_lexer
			exit_status = ft_parser(data);
			
		}
		// system("leaks minishell");
	}
	rl_clear_history();
}
