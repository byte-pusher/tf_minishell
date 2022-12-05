/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 20:38:19 by gjupy             #+#    #+#             */
/*   Updated: 2022/12/04 15:47:16 by rkoop            ###   ########.fr       */
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

void	ft_env(t_env *env_tesh)
{
	if (env_tesh != NULL)
		print_env(&env_tesh);
}
