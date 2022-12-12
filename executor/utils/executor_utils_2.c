/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 17:54:16 by gjupy             #+#    #+#             */
/*   Updated: 2022/12/11 18:20:20 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

bool	ft_check_single_builtin(t_cmd_table *cmd_table)
{
	if (cmd_table->is_builtin == true && cmd_table->is_redir == false
		&& cmd_table->prev == NULL && cmd_table->next == NULL)
		return (true);
	else
		return (false);
}

bool	ft_check_single_cmd(t_cmd_table *cmd_table)
{
	if (cmd_table->is_command == true && cmd_table->is_builtin == false
		&& cmd_table->is_redir == false && cmd_table->next == NULL
		&& cmd_table->prev == NULL)
		return (true);
	else
		return (false);
}
