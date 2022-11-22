/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:56:46 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/22 18:40:11 by gjupy            ###   ########.fr       */
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
	char	*in;

	while (true)
	{
		ft_init_structs(data);
		in = readline(TESHNO);
		data->input = ft_strtrim(in, " ");
		if (ft_strlen(data->input) == 4
			&& ft_strncmp(data->input, "exit", 4) == 0) // danach anders implementieren. ist ein built in
			exit(SUCCESS);
		if (data->input == NULL)
			exit_status = ABORT;
		if (data->input[0] != '\0' && data->input[0] != EOF)
		{
			add_history(data->input);
			ft_lexer(data);				// still need to handle malloc errors in ft_lexer
			ft_parser(data);
			ft_free_all(data);
		}
	}
	ft_lstclear_env(&data->env_tesh);
	rl_clear_history();
	return (exit_status);
}
