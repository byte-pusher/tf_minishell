/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 20:38:19 by gjupy             #+#    #+#             */
/*   Updated: 2022/12/02 15:50:41 by gjupy            ###   ########.fr       */
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
	print_env(&env_tesh);
}

bool	ft_isnum(char c)
{
	if (c >= '0' && c <= '9')
		return (true);
	else
		return (false);
}

void	ft_save_e_code(char *s, int i)
{
	int		end;
	int		start;
	char	*e_code;

	start = i;
	while (s[i] != '\0')
	{
		i++;
		end = i;
	}
	e_code = ft_substr(s, start, end - start);
	g_exit_status = (ft_atoi(e_code));
	free(e_code);
	if (g_exit_status > 255)
		g_exit_status = g_exit_status % 256;
}

void	ft_exit(char *arg, t_data *data)
{
	int	i;
	int	start;

	printf("exit\n");
	i = 4;
	while (ft_is_space(arg[i]) == true)
		i++;
	start = i;
	while (arg[i] != '\0')
	{
		if (ft_is_space(arg[i]) == true)
		{
			g_exit_status = 1;
			ft_err_exit(arg, start, data);
			return ;
		}
		if (ft_isnum(arg[i]) == false)
		{
			g_exit_status = NON_NUM_ARG;
			ft_err_exit(arg, start, data);
			return ;
		}
		i++;
	}
	ft_save_e_code(arg, start);
}
