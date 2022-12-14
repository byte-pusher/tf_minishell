/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 20:15:24 by gjupy             #+#    #+#             */
/*   Updated: 2022/12/14 12:51:10 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	ft_heredoc_loop(t_redir *redir, t_exec *exec, t_cmd_table *cmd_table,
						t_data *data)
{
	int			len_delimiter;
	t_heredoc	heredoc;
	char		*read_nl;

	len_delimiter = ft_strlen(redir->file);
	while (true)
	{
		heredoc.read = readline("> ");
		if (heredoc.read == NULL || g_exit_status == 1)
			break ;
		if (len_delimiter == ft_strlen(heredoc.read)
			&& ft_strncmp(heredoc.read, redir->file, len_delimiter) == 0)
			break ;
		if (cmd_table->expander_delimiter == true
			&& ft_is_var(heredoc.read) == true)
			ft_expand_read(&heredoc, data);
		read_nl = ft_strjoin(heredoc.read, "\n");
		write(exec->here_fd[WRITE], read_nl, ft_strlen(read_nl));
		free(heredoc.read);
		free(read_nl);
	}
	free(heredoc.read);
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
			g_exit_status = 0;
			ft_change_signals();
			ft_heredoc_loop(current, exec, cmd_table, data);
			ft_silence_signals();
		}
		current = current->next;
	}
}
