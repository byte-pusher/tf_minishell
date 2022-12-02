/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:54:51 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/29 18:43:21 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

// bool	ft_is_else_heredoc(t_redir **redir)
// {
	
// }

bool	ft_is_heredoc(t_redir **redir)
{
	t_redir	*current;

	current = *redir;
	while (current != NULL)
	{
		if (current->type == LESSLESS)
			return (true);
		current = current->next;
	}
	return (false);
}

int		ft_count_infiles(t_redir *redir)
{
	int		nbr_of_infiles;
	t_redir	*current;

	nbr_of_infiles = 0;
	current = ft_lstfirst_rd(&redir);
	while (current != NULL)
	{
		if (current->type == LESS)
			nbr_of_infiles++;
		current = current->next;
	}
	return (nbr_of_infiles);
}

bool	ft_heredoc_after_infile(t_redir *redir)
{
	int		j;
	int		nbr_of_infiles;
	t_redir	*current;

	nbr_of_infiles = ft_count_infiles(redir);
	j = 0;
	current = ft_lstfirst_rd(&redir);
	while (current != NULL)
	{
		if (current->type == LESS)
			j++;
		if (j == nbr_of_infiles)
		{
			while (current != NULL)
			{
				if (current->type == LESSLESS)
					return (true);
				current = current->next;
			}
		}
		if (current != NULL)
			current = current->next;
	}
	return (false);
}