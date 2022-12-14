/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:21:13 by gjupy             #+#    #+#             */
/*   Updated: 2022/12/14 12:04:28 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	ft_cmd_err(char *s)
{
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": command not found", 2);
	ft_putstr_fd("\n", 2);
}

void	ft_synt_err(char *s)
{
	ft_putstr_fd("syntax error near unexpected token `", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("'", 2);
	write(STDERR_FILENO, "\n", 2);
}

void	ft_arg_req(char *s)
{
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": filename argument required", 2);
	write(STDERR_FILENO, "\n", 2);
}

void	ft_invalid_err(char *s)
{
	ft_putstr_fd("`", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("': not a valid identifier", 2);
	g_exit_status = 1;
	write(STDERR_FILENO, "\n", 2);
}

void	ft_err_msg(char *s)
{
	write(2, "teshno: ", 8);
	if (g_exit_status == SYNTAX_ERR)
		ft_synt_err(s);
	else if (g_exit_status == CMD_NOT_FOUND)
		ft_cmd_err(s);
	else if (g_exit_status == INVALID_IDENTIFIER)
		ft_invalid_err(s);
	else if (g_exit_status == ARG_REQ)
		ft_arg_req(s);
	else
		perror(s);
}
