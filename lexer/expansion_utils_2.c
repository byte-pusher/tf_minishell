/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 20:32:07 by rkoop             #+#    #+#             */
/*   Updated: 2022/12/14 16:38:05 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	comp_var_len(char *cmd_arg)
{
	int	i;

	i = 0;
	while (cmd_arg[i] != '\0')
	{
		if (cmd_arg[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

int	get_nr_of_vars(char *token_name)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (token_name[i] != '\0')
	{
		if (token_name[i] == '$')
			count++;
		i++;
	}
	return (count);
}

bool	ft_is_double_dollar(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1] == '$')
			return (true);
		i++;
	}
	return (false);
}

int	ft_get_next_var(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

void	ft_insert_dollars(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == 127)
			s[i] = '$';
		i++;
	}
}
