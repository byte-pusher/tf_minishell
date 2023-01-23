/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:56:46 by gjupy             #+#    #+#             */
/*   Updated: 2022/12/14 13:30:54 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

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
	data->unclosed_quotes = false;
	data->exec = NULL;
	data->input = NULL;
	data->empty_input = false;
	data->exit_shell = false;
}

void	ft_init_input(t_data *data)
{
	char	*in;

	in = readline(PURPLE COLOR_BOLD "teshno-1.0$ " COLOR_OFF RESET);
	if (in == NULL)
	{
		printf("exit\n");
		data->exit_shell = true;
		ft_lstclear_env(&data->env_tesh);
		rl_clear_history();
	}
	else if (in[0] == '\0' || ft_is_empty(in) == true)
		data->empty_input = true;
	else
	{
		data->input = ft_strtrim(in, " \t\n");
		if (data->input == NULL)
			exit(ENOMEM);
		if (ft_check_quotes(data->input) == true)
		{
			free(data->input);
			data->unclosed_quotes = true;
		}
	}
	free(in);
}

void	ft_init_teshno(t_data *data)
{
	while (true)
	{
		ft_init_structs(data);
		ft_connect_signals();
		ft_init_input(data);
		ft_silence_signals();
		if (data->exit_shell == true)
			break ;
		if (data->empty_input == true || data->unclosed_quotes == true)
			continue ;
		add_history(data->input);
		if (ft_is_empty(data->input) == false)
		{
			ft_lexer(data);
			expansion(data);
			ft_parser(data);
			ft_executor(data);
			ft_free_all(data);
		}
	}
}
