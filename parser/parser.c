/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:01:14 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/09 20:46:37 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	ft_parser_errors(t_token **token)
{
	if ((*token)->type == PIPE)
	{
		exit_status = SYNTAX_ERR;
		ft_err_msg((*token)->name);
	}
}

int	ft_create_cmd_table(t_token **token)
{
	// while ()
	return (SUCCESS);
}

int	ft_parser(t_token **token)
{
	ft_parser_errors(token);
	ft_create_cmd_table(token);
	ft_lst_clear(token);
	return (SUCCESS);
}
