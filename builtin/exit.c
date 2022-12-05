/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 15:46:27 by rkoop             #+#    #+#             */
/*   Updated: 2022/12/04 15:47:28 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

bool	ft_isnum(char c)
{
	if (c >= '0' && c <= '9')
		return (true);
	else
		return (false);
}

void	ft_save_e_code(char *s)
{
	g_exit_status = (ft_atoi(s));
	if (g_exit_status > 255)
		g_exit_status = g_exit_status % 256;
}

bool	ft_is_non_num(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (ft_isnum(s[i]) == false)
			return (true);
		i++;
	}
	return (false);
}

void	ft_exit(char **cmd_args)
{
	int	i;

	i = 1;
	printf("exit\n");
	if (cmd_args[1] != NULL && cmd_args[2] != NULL)
	{
		ft_err_exit(cmd_args[1], 1);
		return ;
	}
	while (cmd_args[i] != NULL)
	{
		if (ft_is_non_num(cmd_args[i]) == true)
		{
			ft_err_exit(cmd_args[1], NON_NUM_ARG);
			exit (g_exit_status);
		}
		i++;
	}
	if (cmd_args[1] != NULL)
		ft_save_e_code(cmd_args[1]);
	exit (g_exit_status);
}