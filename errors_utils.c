/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:21:13 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/21 16:47:08 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/shell.h"

void	ft_err_msg(char *s)
{
	write(2, "teshno: ", 8);
	if (exit_status == SYNTAX_ERR)
	{
		ft_putstr_fd("syntax error near unexpected token `", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd("'\n", 2);
	}
	else if (exit_status == OPEN_FILE_ERR)
		perror(s);
}
