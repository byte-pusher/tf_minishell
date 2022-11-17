/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:01:14 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/17 17:52:28 by rkoop            ###   ########.fr       */
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

void	ft_create_cmd_table_lst(t_data *data)
{
	t_token	*current;

	lstadd_back_ct(&data->cmd_table, lstnew_ct(&data->cmd_table));
	current = ms_lstfirst(&data->tokens);
	while (current != NULL)
	{
		if (current->type == PIPE)
			lstadd_back_ct(&data->cmd_table, lstnew_ct(&data->cmd_table));
		current = current->next;
	}
}

void	ft_command_parser(t_cmd_table *cmd_table, t_token *token)
{
	cmd_table->cmd_args = ft_split(token->name, ' ');
	cmd_table->is_command = true;
	// execute commands (or at least check If executable)
}

void	ft_create_cmd_table(t_data *data)
{
	t_token		*current_token;
	t_cmd_table	*current_ct; // ct = command table

	ft_create_cmd_table_lst(data);
	current_token = ms_lstfirst(&data->tokens);
	current_ct = lstfirst_ct(&data->cmd_table);
	while (current_token != NULL)
	{
		if (current_token->type == COMMAND)
			ft_command_parser(current_ct, current_token);
		// if (current_token->type == LESS)
		if (current_token->type == PIPE)
			current_ct = current_ct->next;
		current_token = current_token->next;
	}
}

void	free_strings(char ***s)
{
	int	i;

	i = 0;
	while ((*s)[i] != NULL)
	{
		free((*s)[i]);
		i++;
	}
	free((*s)[i]);
	free(*s);
}

void	ft_free_cmd_args(t_cmd_table *cmd_table)
{
	t_cmd_table *current;

	current = lstfirst_ct(&cmd_table);
	while (current != NULL)
	{
		if (current->is_command == true)
			free_strings(&current->cmd_args);
		current = current->next;
	}
}

void	ft_clear_cmd_table(t_cmd_table *cmd_table)
{
	ft_free_cmd_args(cmd_table);
	ft_lstclear_ct(&cmd_table);
}

void	ft_free_all(t_data *data)
{
	ms_lst_clear(&data->tokens);
	// ft_clear_cmd_table(data->cmd_table); // hier kriegen wir errors
}

void	print_cmd_strings(t_cmd_table *cmd_table)
{
	t_cmd_table *current;

	current = lstfirst_ct(&cmd_table);
	while (current != NULL)
	{
		if (current->is_command == true)
		{
			int i = 0;
			while (current->cmd_args[i] != NULL)
			{
				printf("%s ", current->cmd_args[i]);
				i++;
			}
			printf("\n");
		}
		current = current->next;
	}
}

int	ft_parser(t_data *data)
{
	ft_parser_errors(&data->tokens);
	ft_create_cmd_table(data);
	print_cmd_strings(data->cmd_table);
	ft_free_all(data);
	return (SUCCESS);
}
