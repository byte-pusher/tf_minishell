/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:21:13 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/21 18:44:19 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/shell.h"

void	ft_check_redir_err(t_token *token)
{
	if (token->next == NULL)
	{
		exit_status = SYNTAX_ERR;
		ft_err_msg("newline");
	}
	else if (token->next->type == PIPE)
	{
		exit_status = SYNTAX_ERR;
		ft_err_msg(token->next->name);
	}
}

void	ft_cmd_err(char *s)
{
	ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\n", 2);
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
	if (exit_status == SYNTAX_ERR)
		ft_synt_err(s);
	else if (exit_status == OPEN_FILE_ERR)
		perror(s);
	else if(exit_status == CMD_NOT_FOUND)
		ft_cmd_err(s);
}
