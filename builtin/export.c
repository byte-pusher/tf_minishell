/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 15:51:11 by rkoop             #+#    #+#             */
/*   Updated: 2022/11/30 20:15:21 by rkoop            ###   ########.fr       */
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
		i++;
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
	
	while (cmd_args[i] != NULL )
	{
		if (is_var_declaration(cmd_args[i]) == 0)
		{
			ft_lstadd_back_env(&env_tesh, ft_lstnew_env());
			ft_lstlast_env(env_tesh)->var = malloc(sizeof(char) * ft_strlen(cmd_args[i]));
			ft_lstlast_env(env_tesh)->var = cmd_args[i];
		}
		i++;
	}
	//dprintf(2, "last elem var: %s", ft_lstlast_env(env_tesh)->var);
	print_env(&env_tesh);
}
