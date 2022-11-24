/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:56:46 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/24 16:45:12 by rkoop            ###   ########.fr       */
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
		check_quotes(data->input);
		//dprintf(2, "QUOTE STATUS: %s", check_quotes(data->input));
		if (ft_strncmp(data->input, "exit", 4) == 0) // danach anders implementieren. ist ein built in
			break ;
		if (data->input == NULL)
			exit_status = ABORT;
		if (data->input[0] != '\0' && data->input[0] != EOF)
		{
			add_history(data->input);
			ft_lexer(data);	
			ms_print_list(&data->tokens);			// still need to handle malloc errors in ft_lexer
			ft_parser(data);
			ft_free_all(data);
		}
	}
	
	ft_lstclear_env(&data->env_tesh);
	rl_clear_history();
	return (exit_status);
}
