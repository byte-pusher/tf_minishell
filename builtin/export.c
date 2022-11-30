/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 15:51:11 by rkoop             #+#    #+#             */
/*   Updated: 2022/11/27 16:09:43 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	export(t_data *data, char *var)
{
	t_env	*node;
	t_env	*last_node;

	node = NULL;
	last_node = NULL;
	if (var != NULL)
	{
		node = ft_lstnew_env();
		ft_ft_lstadd_back_env(data->env_tesh, node);
		last_node = ft_lstlast_env(data->env_tesh);
		last_node->var = var;
	}
}
