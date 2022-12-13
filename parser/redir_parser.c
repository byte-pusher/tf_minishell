/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:46:26 by gjupy             #+#    #+#             */
/*   Updated: 2022/12/13 13:36:24 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	ft_get_name(t_token **token, t_redir *new_redir)
{
	if ((*token)->name[0] == '\0')
		new_redir->file = "";
	else
		new_redir->file = ft_strdup((*token)->name);
}

void	ft_join_file_name(t_token **token, t_redir *new_redir)
{
	char	*tmp;

	ft_get_name(token, new_redir);
	while ((*token) && ft_is_file_name(*token)
		&& (*token)->mixed_quotes == true)
	{
		if ((*token)->next != NULL && (*token)->next->name[0] != '\0')
		{
			if (new_redir->file[0] == '\0')
				new_redir->file = ft_strdup((*token)->next->name);
			else
			{
				tmp = ft_strdup(new_redir->file);
				if (tmp == NULL)
					exit(ENOMEM);
				free(new_redir->file);
				new_redir->file = ft_strjoin(tmp, (*token)->next->name);
				if (new_redir->file == NULL)
					exit(ENOMEM);
				free(tmp);
			}
		}
		(*token) = (*token)->next;
	}
}

void	ft_redir_parser(t_cmd_table *cmd_table, t_token **token)
{
	t_redir	*new_redir;

	new_redir = ft_lstnew_rd();
	new_redir->type = (*token)->type;
	if ((*token)->next)
		*token = (*token)->next;
	ft_join_file_name(token, new_redir);
	if ((*token)->type == FILE_NAME && (*token)->prev
		&& (*token)->prev->type == LESSLESS)
		cmd_table->expander_delimiter = true;
	cmd_table->is_redir = true;
	ft_lstadd_back_rd(&cmd_table->redir, new_redir);
}
