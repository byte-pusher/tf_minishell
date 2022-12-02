/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:01:14 by gjupy             #+#    #+#             */
/*   Updated: 2022/12/02 16:56:41 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	ft_parser_errors(t_token **token)
{
	t_token	*current;

	if ((*token)->type == PIPE || ft_lstlast_t(*token)->type == PIPE) // still needs to handle pipe in the last position
	{
		exit_status = SYNTAX_ERR;
		ft_err_msg("|");
		return ;
	}
	current = *token;
	while (current != NULL)
	{
		if (ft_is_redir(current->type) == true)
			ft_check_redir_err(current);
		// check for open quotes
		current = current->next;
	}
}

void	ft_create_cmd_table(t_data *data)
{
	t_token		*current_token;
	t_cmd_table	*current_ct; // ct = command table
	char		*combined_name;
	t_token		*cmd_token;

	combined_name = NULL;
	cmd_token = NULL;
	ft_create_cmd_table_lst(data);
	current_token = ft_lstfirst_t(&data->tokens);
	current_ct = ft_lstfirst_ct(&data->cmd_table);
	while (current_token != NULL)
	{
		if (current_token->type == COMMAND)
		{
			cmd_token = current_token;
			if (current_token->next && (current_token->next->type == DQUOTE || current_token->next->type == SQUOTE))
			{
				combined_name = (char *)malloc(sizeof(char) * get_combined_len(current_token));
				ft_strncpy(combined_name, current_token->name, get_combined_len(current_token));
				current_token = current_token->next;
				while (current_token && (current_token->type == DQUOTE || current_token->type == SQUOTE || current_token->type == COMMAND ))
				{
					cmd_token->name = ft_strjoin(cmd_token->name, current_token->name);
					cmd_token->name = ft_strjoin(cmd_token->name, " ");
					current_token = current_token->next;
				}
				free(combined_name);
			}
			ft_command_parser(current_ct, cmd_token, data);
		
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
	if (exit_status != SYNTAX_ERR)
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
