/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:56:46 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/28 18:18:34 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/shell.h"

void	ft_init_structs(t_data *data)
{
	data->tokens = NULL;
	data->cmd_table = NULL;
	data->exec = NULL;
	// was muss noch initialisiert werden?
}

void	ft_init_input(t_data *data)
{
	char	*in;

	in = readline(TESHNO);
	data->input = ft_strtrim(in, " ");
	if (data->input == NULL)
		exit(ENOMEM);
}

int	ft_init_teshno(t_data *data)
{
	while (true)
	{
		ft_init_structs(data);
		ft_init_input(data);
		if (ft_strlen(data->input) == 4
			&& ft_strncmp(data->input, "exit", 4) == 0)
			exit(SUCCESS);
		if (data->input[0] != '\0' && data->input[0] != EOF)
		{
			add_history(data->input);
			ft_lexer(data);
			expansion(data);
			ft_parser(data);
			ft_executor(data);
			ft_free_all(data);
		}
	}
	// entweder freen oder einfach exit
	// actually the OS reclaims the mem allocated in the program after exit
	// downside: When you leave memory allocated at the end of the program you never know whether you have a leak
	// so maybe it makes sense to exit only when we have a ENOMEM
	ft_lstclear_env(&data->env_tesh);
	free(data->input);
	rl_clear_history();
	return (exit_status);
}
