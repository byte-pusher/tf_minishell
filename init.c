/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:56:46 by gjupy             #+#    #+#             */
/*   Updated: 2022/12/08 19:27:53 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/shell.h"

bool	ft_is_empty(char *input)
{
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		if (ft_is_space(input[i]) == false)
			return (false);
		i++;
	}
	return (true);
}

void	ft_init_structs(t_data *data)
{
	data->tokens = NULL;
	data->cmd_table = NULL;
	data->exec = NULL;
	data->exit_shell = false;
}

void	ft_init_input(t_data *data)
{
	char	*in;

	in = readline(TESHNO);
	if (in == NULL)
	{
		data->exit_shell = true;
		ft_lstclear_env(&data->env_tesh);
		rl_clear_history();
	}
	else
	{
		data->input = ft_strtrim(in, " \t\n");
		if (data->input == NULL)
			exit(ENOMEM);
	}
	free(in);
}

void	ft_init_teshno(t_data *data)
{
	while (true)
	{
		ft_init_structs(data);
		ft_init_input(data);
		if (data->exit_shell == true)
			break ;
		add_history(data->input);
		if (ft_is_empty(data->input) == true)
			free(data->input);
		else
		{
			ft_lexer(data);
			expansion(data);
			ft_parser(data);
			ft_executor(data);
			ft_free_all(data);
		}
	}
}
