/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 15:28:21 by rkoop             #+#    #+#             */
/*   Updated: 2022/11/29 19:59:57 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

//removes var rom env and sehll vars
//basic function ready, working for several vars in one cmd? e.g. unset USER LANG
void	ft_unset(char **cmd_args, t_env *env_tesh)
{
	t_env 	*current_env;
	int 	i;

	current_env = env_tesh;
	i = 1;

	if (cmd_args[1] != NULL)
	{
		while (cmd_args[i] != NULL)
		{
			//remove from env
			while (current_env != NULL)
			{
				if (ft_strnstr(current_env->var, cmd_args[i], ft_strlen(current_env->var)) != NULL)
				{
					dprintf(2, "\nfound");
					ft_lstdel_env(env_tesh, current_env);
				}	
				current_env = current_env->next;
			}
			i++;
		}
	}
}
