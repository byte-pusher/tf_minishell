/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 20:38:19 by gjupy             #+#    #+#             */
/*   Updated: 2022/12/14 16:51:51 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

bool	ft_is_flag(char **cmd_args)
{
	int	j;

	if (cmd_args[1][1] != '\0' && cmd_args[1][0] == '-'
		&& cmd_args[1][1] == 'n')
	{
		j = 2;
		while (cmd_args[1][j])
		{
			if (cmd_args[1][j] != 'n')
				return (false);
			j++;
		}
	}
	else
		return (false);
	return (true);
}

void	ft_skip_flags(char **cmd_args, int *i)
{
	int	j;

	*i = 2;
	while (cmd_args[*i] != NULL)
	{
		if (cmd_args[*i][1] != '\0' && cmd_args[*i][0] == '-'
			&& cmd_args[*i][1] == 'n')
		{
			j = 2;
			while (cmd_args[*i][j])
			{
				if (cmd_args[*i][j] != 'n')
					return ;
				j++;
			}
		}
		else
			return ;
		(*i)++;
	}
}

void	ft_echo(char **cmd_args)
{
	int		i;
	bool	is_flag;

	i = 1;
	is_flag = false;
	if (cmd_args[1] != NULL)
	{
		is_flag = ft_is_flag(cmd_args);
		if (is_flag == true)
			ft_skip_flags(cmd_args, &i);
		while (cmd_args[i] != NULL)
		{
			printf("%s", cmd_args[i]);
			if (cmd_args[i + 1] != NULL)
				printf(" ");
			i++;
		}
	}
	if (is_flag == false)
		printf("\n");
}
