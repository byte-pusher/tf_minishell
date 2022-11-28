/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 15:28:21 by rkoop             #+#    #+#             */
/*   Updated: 2022/11/27 20:38:09 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

//TD
//change eng lst to double linked list
//create del ft or implement directly in unser

void	unset(t_data *data, char *var)
{
	t_env 	*current_env;

	current_env = data->env_tesh;

	while (current_env != NULL)
	{
		if (ft_strnstr(current_env->var, var + 1, ft_strlen(current_env->var)) != NULL)
		//...
	}
	current_env = current_env->next;
	
}