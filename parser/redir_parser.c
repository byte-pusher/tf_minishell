/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:46:26 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/28 15:04:13 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	open_file(t_redir *redir)
{
	if (redir->type == LESS) // in
		redir->fd = open(redir->file, O_RDONLY);
	else if (redir->type == GREAT) // out
		redir->fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (redir->type == GREATGREAT || redir->type == LESSLESS)	// append or heredoc
		redir->fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (redir->fd == -1)
	{
		exit_status = OPEN_FILE_ERR;
		ft_err_msg(redir->file);
	}
}

void	ft_redir_parser(t_cmd_table *cmd_table, t_token **token)
{
	t_redir	*new_redir;

	new_redir = ft_lstnew_rd();
	new_redir->type = (*token)->type;
	*token = (*token)->next;
	new_redir->file = ft_strdup((*token)->name); // next is file_name
	if (new_redir->file == NULL)
		exit(ENOMEM);
	// open_file(new_redir);
	cmd_table->is_redir = true;
	ft_lstadd_back_rd(&cmd_table->redir, new_redir);
}
