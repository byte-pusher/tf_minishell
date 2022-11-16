/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:01:14 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/16 17:24:50 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	ft_parser_errors(t_token **token)
{
	// hier maybe ein loop schreiben um nach Fehlern zu schauen
	if ((*token)->type == PIPE) // or pipe in the last position
	{
		exit_status = SYNTAX_ERR;
		ft_err_msg((*token)->name);
	}
}

void	ft_init_cmd_table(t_data *data)
{
	t_token	*current;

	data->cmd_line = malloc(sizeof(t_cmd_line));
	data->cmd_line->nbr_of_cmds = 1;
	current = ms_lstfirst(&data->tokens);
	while (current != NULL)
	{
		if (current->type == PIPE)
			data->cmd_line->nbr_of_cmds++;
		current = current->next;	
	}
	data->cmd_line->cmds = malloc(sizeof(data->cmd_line->cmds) * data->cmd_line->nbr_of_cmds);
}

//get 2 d array of commands with their args
void	ft_create_cmd_args(t_data *data)
{
	//create current
	t_token	*current;
	int		i;

	current = ms_lstfirst(&data->tokens);
	//loop trough tokens
	i = -1;
	while (++i < data->cmd_line->nbr_of_cmds)
	{
		data->cmd_line->cmds[i].nbr_of_args = 0;
		if (current != NULL && current->type == PIPE)
			current = current->next;
		while (current != NULL && current->type != PIPE)
		{
			if (current->type == COMMAND)
			{
				dprintf(2, "index: %d\n", i);
				data->cmd_line->cmds[i].cmd_args = ft_split(current->name, ' ');
				dprintf(2, "%s\n", data->cmd_line->cmds[0].cmd_args[0]);
				data->cmd_line->cmds->nbr_of_args++;
			}
			current = current->next;
		}
	}
}

int	ft_create_cmd_table(t_data *data)
{
	ft_init_cmd_table(data);
	ft_create_cmd_args(data);
	return (SUCCESS);
}

void	free_strings(char ***s, int len)
{
	while (len >= 0)
	{
		dprintf(2, "%d\n", len);
		free((*s)[len]);
		len--;
	}
	dprintf(2, "jo\n");
	free(*s);
}

void	ft_clear_cmd_table(t_cmd_line *cmd_line)
{
	int	i;
	int	j;

	i = -1;
	// while (++i < cmd_line->nbr_of_cmds)
	// 	free_strings(&cmd_line->cmds[i].cmd_args, cmd_line->cmds[i].nbr_of_args);
	free(cmd_line->cmds);
}

void	ft_free_all(t_data *data)
{
	ms_lst_clear(&data->tokens);
	ft_clear_cmd_table(data->cmd_line);
}

int	ft_parser(t_data *data)
{
	ft_parser_errors(&data->tokens);
	ft_create_cmd_table(data);
	// printf("%s\n", data->cmd_line->cmds[0].cmd_args[0]);
	ft_free_all(data);
	return (SUCCESS);
}
