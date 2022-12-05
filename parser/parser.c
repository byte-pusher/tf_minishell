/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:01:14 by gjupy             #+#    #+#             */
/*   Updated: 2022/12/05 23:33:45 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	ft_parser_errors(t_token **token)
{
	t_token	*current;

	if ((*token)->type == PIPE || ft_lstlast_t(*token)->type == PIPE)
	{
		g_exit_status = SYNTAX_ERR;
		ft_err_msg("|");
		return ;
	}
	current = *token;
	while (current != NULL)
	{
		if (current->next != NULL && current->type == PIPE && current->next->type == PIPE)
		{
			g_exit_status = SYNTAX_ERR;
			ft_err_msg("|");
			return ;
		}
		if (ft_is_redir(current->type) == true)
		{
			ft_check_redir_err(current);
			if (g_exit_status == SYNTAX_ERR)
				return ;
		}
		// check for open quotes. SYNTAX ERROR
		current = current->next;
	}
	g_exit_status = SUCCESS;
}

void	ft_create_cmd_table(t_data *data)
{
	t_token		*current_token;
	t_cmd_table	*current_ct;

	ft_create_cmd_table_lst(data);
	current_token = ft_lstfirst_t(&data->tokens);
	current_ct = ft_lstfirst_ct(&data->cmd_table);
	while (current_token != NULL)
	{
		if (ft_is_cmd_or_quotes(current_token) == true)
		{
			if (current_token->type == COMMAND && current_token->prev != NULL
				&& current_token->prev->type == LESSLESS)
				current_ct->expander_delimiter = true;
			ft_command_parser(current_ct, &current_token, data);
		}
		if (current_token != NULL)
		{
			if (ft_is_redir(current_token->type))
				ft_redir_parser(current_ct, &current_token);
			if (current_token->type == PIPE)
				current_ct = current_ct->next;
		}
		if (current_token != NULL)
			current_token = current_token->next;
	}
}

void	ft_parser(t_data *data)
{
	ft_parser_errors(&data->tokens);
	if (g_exit_status != SYNTAX_ERR)
		ft_create_cmd_table(data);
	// print_cmd_strings(data->cmd_table);
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
