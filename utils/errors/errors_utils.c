/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:21:13 by gjupy             #+#    #+#             */
/*   Updated: 2022/12/02 19:53:53 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	ft_cmd_err(char *s)
{
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": command not found", 2);
	ft_putstr_fd("\n", 1);
}

void	ft_synt_err(char *s)
{
	ft_putstr_fd("syntax error near unexpected token `", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("'", 2);
	write(STDERR_FILENO, "\n", 1);
}

void	ft_err_msg(char *s)
{
	write(2, "teshno: ", 8);
	if (g_exit_status == SYNTAX_ERR)
		ft_synt_err(s);
	else if (g_exit_status == CMD_NOT_FOUND)
		ft_cmd_err(s);
	else
		perror(s);
}

void	ft_err_exit(char *s, int e_status)
{
	g_exit_status = e_status;
	ft_putstr_fd("teshno: exit: ", 2);
	if (g_exit_status == NON_NUM_ARG)
	{
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
	else if (g_exit_status == 1)
		ft_putstr_fd("too many arguments\n", 2);
}
