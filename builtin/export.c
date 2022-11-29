/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 15:51:11 by rkoop             #+#    #+#             */
/*   Updated: 2022/11/29 20:15:11 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

//add vars to envs, but simple way. export demo=jo
//also works in dquotes and squotes


int		is_var_declaration(char *cmd_arg)
{
	int 	i;
	
	i = 0;
	while(cmd_arg[i] != '\0')
	{
		if (cmd_arg[i] == '=')
			return(0);
	}
	return(1);
}


void	ft_export(char **cmd_args, t_env *env_tesh)
{
	t_env	*node;
	t_env	*last_node;
	int		i;

	node = NULL;
	last_node = NULL;
	i = 1;

	if (cmd_args[1] != NULL)
	{
		while (cmd_args[i] != NULL )
		{
			if (is_var_declaration(cmd_args[i]) == 0)
			{
				node = ft_lstnew_env();
				ft_lstadd_back_env(&env_tesh, node);
				last_node = ft_lstlast_env(env_tesh);
				last_node->var = cmd_args[i];
			}
			i++;
		}
	}
}
