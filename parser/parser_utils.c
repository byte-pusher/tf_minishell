/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:32:11 by gjupy             #+#    #+#             */
/*   Updated: 2022/12/07 19:35:16 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

bool	ft_is_redir(int type)
{
	if (type == GREAT || type == GREATGREAT || type == LESS
		|| type == LESSLESS)
		return (true);
	return (false);
}

bool	ft_check_redir_err(t_token *token)
{
	if (token->next == NULL)
	{
		g_exit_status = SYNTAX_ERR;
		ft_err_msg("newline");
		return (true);
	}
	else if (token->next->type != FILE_NAME && token->type != LESSLESS)
	{
		g_exit_status = SYNTAX_ERR;
		ft_err_msg(token->next->name);
		return (true);
	}
	return (false);
}

void	ft_create_cmd_table_lst(t_data *data)
{
	t_token	*current;

	ft_lstadd_back_ct(&data->cmd_table, ft_lstnew_ct());
	current = ft_lstfirst_t(&data->tokens);
	while (current != NULL)
	{
		if (current->type == PIPE)
			ft_lstadd_back_ct(&data->cmd_table, ft_lstnew_ct());
		current = current->next;
	}
}

bool	ft_is_cmd_or_quotes(t_token *token)
{
	if (token->type == COMMAND || token->type == SQUOTE || token->type == DQUOTE)
		return (true);
	else
		return (false);
}

// void	print_cmd_strings(t_cmd_table *cmd_table)
// {
// 	t_cmd_table	*current;
// 	int			i;

// 	current = ft_lstfirst_ct(&cmd_table);
// 	while (current != NULL)
// 	{
// 		if (current->is_command == true)
// 		{
// 			i = 0;
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

// int		get_combined_len(t_token *current_token)
// {
// 	t_token	*tmp;
// 	int 	len;

// 	tmp = current_token->next;
// 	len = ft_strlen(current_token->name);
// 	while (tmp && (tmp->type == DQUOTE || tmp->type == SQUOTE))
// 	{
// 			len = len + ft_strlen(tmp->name);
// 			tmp = tmp->next;	
// 	}
// 	return(len);
// }
