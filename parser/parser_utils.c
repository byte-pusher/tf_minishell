/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:32:11 by gjupy             #+#    #+#             */
/*   Updated: 2022/12/13 16:15:30 by gjupy            ###   ########.fr       */
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
	else if (ft_is_redir(token->next->type) || token->next->type == PIPE)
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
	if (token->type == COMMAND || token->type == SQUOTE
		|| token->type == DQUOTE)
		return (true);
	else
		return (false);
}
