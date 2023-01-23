/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:15:27 by gjupy             #+#    #+#             */
/*   Updated: 2022/12/14 16:03:59 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	print_env(t_env **lst, t_data *data)
{
	t_env	*current;

	if (data->env_exists == false)
		return ;
	current = *lst;
	while (current != NULL)
	{
		if (current && current->hidden == false && current->var != NULL)
			printf("%s\n", current->var);
		current = current->next;
	}
}

void	ft_create_env_lst(t_env **env_tesh, char *s)
{
	t_env	*new_env;

	new_env = ft_lstnew_env();
	new_env->var = ft_strdup(s);
	ft_lstadd_back_env(env_tesh, new_env);
}

void	ft_create_empty_env(t_env **env_tesh)
{
	t_env	*new_env;
	t_env	*head_node;
	t_env	*last_env;
	char	*tmp;
	char	*buffer;

	buffer = NULL;
	head_node = ft_lstnew_env();
	tmp = getcwd(buffer, 0);
	ft_lstadd_back_env(env_tesh, head_node);
	new_env = ft_lstnew_env();
	ft_lstadd_back_env(env_tesh, new_env);
	ft_lstlast_env(*env_tesh)->var = malloc(ft_strlen(tmp) + 8);
	ft_strncpy(ft_lstlast_env(*env_tesh)->var, "PWD=", ft_strlen(tmp) + 8);
	last_env = ft_lstlast_env(*env_tesh);
	last_env->var = ft_strjoin(last_env->var, tmp);
	free(buffer);
	free(tmp);
}

void	ft_get_env(char **env, t_data *data)
{
	int	i;

	i = 0;
	if (data->env_exists == false)
		return ;
	if (env[i] == NULL)
		ft_create_empty_env(&data->env_tesh);
	while (env[i])
	{
		ft_create_env_lst(&data->env_tesh, env[i]);
		i++;
	}
	data->env_exists = true;
}
