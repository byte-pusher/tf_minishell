/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 23:48:05 by gjupy             #+#    #+#             */
/*   Updated: 2022/12/12 23:50:18 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	ft_err_exit(char *s, int e_status, t_data *data)
{
	g_exit_status = e_status;
	ft_putstr_fd("teshno: exit: ", 2);
	if (g_exit_status == NON_NUM_ARG)
	{
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		ft_free_all(data);
		ft_lstclear_env(&data->env_tesh);
		rl_clear_history();
		exit(g_exit_status);
	}
	else if (g_exit_status == 1)
		ft_putstr_fd("too many arguments\n", 2);
}

bool	ft_is_path_cmd(char *s)
{
	write(2, "teshno: ", 8);
	if ((ft_strlen(s) == 1 && s[0] == '/')
		|| ((ft_strlen(s) == 2) && ft_strncmp(s, "./", 2) == 0))
	{
		g_exit_status = IS_DIR;
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": is a directory", 2);
	}
	else if ((ft_strncmp(s, "./", 2) == 0 && ft_strlen(s) > 2)
		|| (ft_strncmp(s, "/", 1) == 0 && ft_strlen(s) > 1))
	{
		g_exit_status = CMD_NOT_FOUND;
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": No such file or directory", 2);
	}
	else
		return (false);
	ft_putstr_fd("\n", 2);
	return (true);
}
