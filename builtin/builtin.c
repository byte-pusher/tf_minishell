/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 20:38:19 by gjupy             #+#    #+#             */
/*   Updated: 2022/12/11 17:52:09 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"



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

// void	ft_env(t_env *env_tesh)
// {
// 	if (env_tesh != NULL)
// 		print_env(&env_tesh);
// }
