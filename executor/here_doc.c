/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 20:15:24 by gjupy             #+#    #+#             */
/*   Updated: 2022/12/07 17:05:08 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	ft_heredoc_loop(t_redir *redir, t_exec *exec, t_cmd_table *cmd_table, t_data *data)
{
	int			len_delimiter;
	t_heredoc	heredoc;
	// char	*read;
	char	*read_nl;

	len_delimiter = ft_strlen(redir->file);
	while (true)
	{
		heredoc.read = readline("> ");
		if (heredoc.read == NULL)
			break ;
		if (len_delimiter == ft_strlen(heredoc.read)
			&& ft_strncmp(heredoc.read, redir->file, len_delimiter) == 0)
			break ;
		if (cmd_table->expander_delimiter == true && ft_is_var(heredoc.read) == true)
			ft_expand_read(&heredoc, data);

		read_nl = ft_strjoin(heredoc.read, "\n");
		write(exec->here_fd[WRITE], read_nl, ft_strlen(read_nl));
		// free(read);
		free(heredoc.read);
		free(read_nl);
	}
	free(heredoc.read);
	// dup2(exec->here_fd[READ], exec->tmp_fd);
	dup2(exec->here_fd[READ], cmd_table->here_tmp_fd);
	close(exec->here_fd[READ]);
	close(exec->here_fd[WRITE]);
}

void	ft_heredoc(t_exec *exec, t_cmd_table *cmd_table, t_data *data)
{
	t_redir	*current;

	current = ft_lstfirst_rd(&cmd_table->redir);
	while (current != NULL)
	{
		if (current->type == LESSLESS)
		{
			pipe(exec->here_fd);
			ft_heredoc_loop(current, exec, cmd_table, data);
		}
		current = current->next;
	}
}
