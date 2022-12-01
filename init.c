/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:56:46 by gjupy             #+#    #+#             */
/*   Updated: 2022/12/01 18:03:51 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/shell.h"

bool	ft_exit_cmd(t_data *data)
{
	if (ft_strlen(data->input) >= 4)
	{
		if (data->input[0] == 'e' && data->input[1] == 'x'
			&& data->input[2] == 'i' && data->input[3] == 't')
		{
			if (data->input[4] == '\0')
			{
				printf("exit\n");
				return (true);
			}
			if (ft_is_space(data->input[4]) == true)
			{
				ft_exit(data->input, data);
				return (true);
			}
		}
	}
	return (false);
}

void	ft_init_structs(t_data *data)
{
	data->tokens = NULL;
	data->cmd_table = NULL;
	data->exec = NULL;
	data->exit_in_err = false;
	// was muss noch initialisiert werden?
}

void	ft_init_input(t_data *data)
{
	char	*in;

	in = readline(TESHNO);
	data->input = ft_strtrim(in, " ");
	free(in);
	if (data->input == NULL)
		exit(ENOMEM);
}

void	ft_init_teshno(t_data *data)
{
	while (true)
	{
		ft_init_structs(data);
		ft_init_input(data);
		add_history(data->input);
		if (ft_exit_cmd(data) == true)
		{
			if (data->exit_in_err == true && g_exit_status == 1)
			{
				free(data->input);
				continue ;
			}
			else
				break ;
		}
		if (data->input[0] != '\0' && data->input[0] != EOF)
		{
			ft_lexer(data);
			expansion(data);
			ft_parser(data);
			if (g_exit_status != SYNTAX_ERR)
				ft_executor(data);
			ft_free_all(data);
		}
	}
	ft_lstclear_env(&data->env_tesh);
	free(data->input);
	rl_clear_history();
}
