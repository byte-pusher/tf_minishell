/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 15:17:23 by gjupy             #+#    #+#             */
/*   Updated: 2022/08/12 21:12:58 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

bool	is_space(char c)
{
	if (c == ' ')
		return (true);
	return (false);
}

bool	str_of_spaces(char *argv)
{
	int		i;
	int		j;

	i = 0;
	while (argv[i])
	{
		while (is_space(argv[i]))
			i++;
		if (argv[i] != '\0')
			break ;
		else if (argv[i] == '\0')
			return (true);
		i++;
	}
	return (false);
}

/*
only returns error if it is not delimiter string (argv[2])
*/
int	check_cmd_strs_here_doc(char **s, t_pipex *pipex)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (i != 2)
		{
			if (s[i][0] == '\0' || str_of_spaces(s[i]) == true)
				return (-1);
		}
		i++;
	}
	return (0);
}

int	check_cmd_strs(char **s, t_pipex *pipex)
{
	if (pipex->here_doc == true)
		return (check_cmd_strs_here_doc(s, pipex));
	while (*s)
	{
		if (**s == '\0' || str_of_spaces(*s) == true)
			return (-1);
		s++;
	}
	return (0);
}

bool	is_here_doc(t_pipex *pipex, char **argv)
{
	if (ft_strncmp("here_doc", argv[1], 8) == 0)
	{
		pipex->here_doc = true;
		pipex->delimiter = argv[2];
		return (true);
	}
	else
	{
		pipex->here_doc = false;
		return (false);
	}
}
