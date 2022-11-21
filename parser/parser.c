/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:01:14 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/21 13:49:58 by gjupy            ###   ########.fr       */
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

void	ft_create_cmd_table(t_data *data)
{
	t_token		*current_token;
	t_cmd_table	*current_ct; // ct = command table

	ft_create_cmd_table_lst(data);
	current_token = ft_lstfirst_t(&data->tokens);
	current_ct = ft_lstfirst_ct(&data->cmd_table);
	while (current_token != NULL)
	{
		if (current_token->type == COMMAND)
			ft_command_parser(current_ct, current_token);
		if (ft_is_redir(current_token->type))
			ft_redir_parser(current_ct, &current_token);
		if (current_token->type == PIPE)
			current_ct = current_ct->next;
		current_token = current_token->next;
	}
}

int	ft_parser(t_data *data)
{
	ft_parser_errors(&data->tokens);
	ft_create_cmd_table(data);
	return (SUCCESS);
}

// void	print_rd(t_data *data)
// {
// 	t_cmd_table *current;
// 	current = ft_lstfirst_ct(&data->cmd_table);
// 	while (current)
// 	{
// 		if (current->is_redir == true)
// 		{
// 			t_redir *current_r = current->redir->head;
// 			while (current_r != NULL)
// 			{
// 				printf("%s\n", current_r->file);
// 				current_r = current_r->next;
// 			}
// 			current = current->next;
// 		}
// 	}
// }

// void	print_cmd_strings(t_cmd_table *cmd_table)
// {
// 	t_cmd_table *current;

// 	current = ft_lstfirst_ct(&cmd_table);
// 	while (current != NULL)
// 	{
// 		if (current->is_command == true)
// 		{
// 			int i = 0;
// 			while (current->cmd_args[i] != NULL)
// 			{
// 				printf("%s ", current->cmd_args[i]);
// 				i++;
// 			}
// 			printf("\n");
// 		}
// 		current = current->next;
// 	}
// }
