/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:01:14 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/15 22:34:16 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	ft_parser_errors(t_token **token)
{
	if ((*token)->type == PIPE)
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

void	ft_create_cmd_args_1(t_data *data)
{
	t_token	*current;
	int		i;

	current = ms_lstfirst(&data->tokens);
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
				while (current != NULL && current->type == COMMAND)
				{
					data->cmd_line->cmds[i].nbr_of_args++;
					current = current->next;
				}
			}
			else
				current = current->next;
		}
		dprintf(2, "nbr of args: %d\n", data->cmd_line->cmds[i].nbr_of_args);
		data->cmd_line->cmds[i].cmd_args = malloc((sizeof(char *) * (data->cmd_line->cmds[i].nbr_of_args + 1)));
	}
}

void	ft_create_cmd_args_2(t_data *data)
{
	t_token	*current;
	int		i;
	int		j;

	current = ms_lstfirst(&data->tokens);
	i = -1;
	while (++i < data->cmd_line->nbr_of_cmds)
	{
		if (current != NULL && current->type == PIPE)
			current = current->next;
		while (current != NULL && current->type != PIPE)
		{
			if (current->type == COMMAND)
			{
				j = 0;
				while (current != NULL && current->type == COMMAND)
				{
					dprintf(2, "i: %d j: %d type: %d name: %s\n", i, j, current->type, current->name);
					data->cmd_line->cmds[i].cmd_args[j] = ft_strdup(current->name); // the problem is with the cmds list or cmd_args DArray
					dprintf(2, "%s\n", data->cmd_line->cmds[i].cmd_args[j]);
					j++;
					current = current->next;
				}
				data->cmd_line->cmds[i].cmd_args[j] = NULL;
			}
			else
				current = current->next;
		}
	}
}

int	ft_create_cmd_table(t_data *data)
{
	ft_init_cmd_table(data);
	ft_create_cmd_args_1(data);
	ft_create_cmd_args_2(data);
	// ft_init_files(data);
	return (SUCCESS);
}

int	ft_parser(t_data *data)
{
	ft_parser_errors(&data->tokens);
	ft_create_cmd_table(data);
	ms_lst_clear(&data->tokens);
	return (SUCCESS);
}
