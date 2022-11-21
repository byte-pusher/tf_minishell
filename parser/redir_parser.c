/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:46:26 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/21 13:46:54 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	ft_redir_parser(t_cmd_table *cmd_table, t_token **token)
{
	t_redir	*new_redir;

	new_redir = ft_lstnew_rd();
	new_redir->type = (*token)->type;
	*token = (*token)->next;
	new_redir->file = ft_strdup((*token)->name); // next is file_name
	cmd_table->is_redir = true;
	ft_lstadd_back_rd(&cmd_table->redir, new_redir);
}
