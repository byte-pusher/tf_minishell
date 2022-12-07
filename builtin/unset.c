/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 15:28:21 by rkoop             #+#    #+#             */
/*   Updated: 2022/12/05 20:58:02 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	ft_unset(char **cmd_args, t_env *env_tesh)
{
	t_env	*current_env;
	int		i;

	current_env = NULL;
	i = 1;
	while (cmd_args[i] != NULL)
	{
		current_env = ft_lstfirst_env(&env_tesh);
		while (current_env != NULL)
		{
			if (ft_strnstr(current_env->var, cmd_args[i],
					ft_strlen(current_env->var)) != NULL)
			{
				ft_lstdel_env(env_tesh, current_env);
			}	
			current_env = current_env->next;
		}
		i++;
	}
}
