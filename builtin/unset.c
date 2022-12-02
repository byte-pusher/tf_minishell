/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 15:28:21 by rkoop             #+#    #+#             */
/*   Updated: 2022/11/30 20:16:45 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	ft_unset(char **cmd_args, t_env *env_tesh)
{
	t_env 	*current_env;
	int 	i;

	current_env = NULL;
	i = 1;
	while (cmd_args[i] != NULL)
	{
		//remove from env
		current_env = env_tesh;
		while (current_env != NULL)
		{
			if (ft_strnstr(current_env->var, cmd_args[i], ft_strlen(current_env->var)) != NULL)
			{
				ft_lstdel_env(env_tesh, current_env);
			}	
			current_env = current_env->next;
		}
		i++;
	}
}
