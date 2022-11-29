/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 20:15:24 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/29 21:08:04 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	ft_heredoc_loop(t_redir *redir, t_exec *exec)
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
	dup2(exec->here_fd[READ], exec->tmp_fd);
	close(exec->here_fd[READ]);
	close(exec->here_fd[WRITE]);
}

void	ft_heredoc(t_redir *redir, t_exec *exec)
{
	t_redir	*current;

	current = ft_lstfirst_rd(&redir);
	while (current != NULL)
	{
		if (current->type == LESSLESS)
		{
			pipe(exec->here_fd);
			ft_heredoc_loop(current, exec);
		}
		dprintf(2, "raus\n");
		current = current->next;
	}
}
