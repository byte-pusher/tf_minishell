/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 20:15:24 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/30 20:20:59 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	ft_heredoc_loop(t_redir *redir, t_exec *exec, t_cmd_table *cmd_table)
{
	int		len_delimiter;
	char	*read;
	char	*read_nl;

	len_delimiter = ft_strlen(redir->file);
	while (true)
	{
		read = readline("> ");
		if (len_delimiter == ft_strlen(read)
			&& ft_strncmp(read, redir->file, len_delimiter) == 0)
				break ;
		read_nl = ft_strjoin(read, "\n");
		write(exec->here_fd[WRITE], read_nl, ft_strlen(read_nl));
		free(read);
		free(read_nl);
	}
	free(read);
	// dup2(exec->here_fd[READ], exec->tmp_fd);
	dup2(exec->here_fd[READ], cmd_table->here_tmp_fd);
	close(exec->here_fd[READ]);
	close(exec->here_fd[WRITE]);
}

void	ft_heredoc(t_exec *exec, t_cmd_table *cmd_table)
{
	t_redir	*current;

	current = ft_lstfirst_rd(&cmd_table->redir);
	while (current != NULL)
	{
		if (current->type == LESSLESS)
		{
			pipe(exec->here_fd);
			ft_heredoc_loop(current, exec, cmd_table);
		}
		current = current->next;
	}
}
