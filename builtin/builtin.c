/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 20:38:19 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/24 00:31:18 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	ft_exit(void)
{
	printf("\n");
	printf("exit");
	exit(SUCCESS);
}

void	ft_echo(char **cmd_args)
{
	int		i;
	bool	is_flag;

	i = 1;
	is_flag = false;
	// noch bugs bei echo -n + --n || --
	if (cmd_args[1] != NULL)
	{
		is_flag = ft_is_flag(cmd_args);
		if (is_flag == true)
			ft_skip_flags(cmd_args, &i);
		while (cmd_args[i] != NULL)
		{
			printf("%s ", cmd_args[i]);
			i++;
		}
	}
	else if (cmd_args[2] == NULL)
		printf("%s", cmd_args[1]);
	if (is_flag == false)
		printf("\n");
}

void	ft_env(t_env *env_tesh)
{
	print_env(&env_tesh);
}
