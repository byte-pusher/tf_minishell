/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:32:11 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/17 17:34:28 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

bool	ft_is_redir(int type)
{
	if (type == GREAT || type == GREATGREAT || type == LESS
		|| type == LESSLESS)
			return (true);
	return (false);
}
