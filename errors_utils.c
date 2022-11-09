/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:21:13 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/09 18:58:00 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/shell.h"

void	ft_err_msg(char *token)
{
	if (exit_status == SYNTAX_ERR)
		printf("teshno: syntax error near unexpected token `%s'\n", token);
}
