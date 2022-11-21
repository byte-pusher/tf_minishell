/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:45:09 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/21 13:45:54 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	ft_command_parser(t_cmd_table *cmd_table, t_token *token)
{
	cmd_table->cmd_args = ft_split(token->name, ' ');
	cmd_table->is_command = true;
	// execute commands (or at least check If executable)
}
