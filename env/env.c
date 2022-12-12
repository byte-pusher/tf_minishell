/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 21:40:05 by gjupy             #+#    #+#             */
/*   Updated: 2022/12/12 20:37:10 by rkoop            ###   ########.fr       */
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
		if (current->hidden == false && current->var != NULL)
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
	char	*tmp;
	char	*buffer;
	char	pwd_var[] = "PWD=";

	buffer = NULL;
	head_node = ft_lstnew_env();
	ft_lstadd_back_env(env_tesh, head_node);
	new_env = ft_lstnew_env();
	ft_lstadd_back_env(env_tesh, new_env);
	ft_lstlast_env(*env_tesh)->var = malloc(sizeof(char) * (ft_strlen(getcwd(buffer, 0)) + 8));
	ft_strncpy(ft_lstlast_env(*env_tesh)->var, pwd_var, ft_strlen(getcwd(buffer, 0)) + 8);
	ft_lstlast_env(*env_tesh)->var = ft_strjoin(ft_lstlast_env(*env_tesh)->var, getcwd(buffer, 0));
	free(buffer);
}

void	ft_get_env(char **env, t_data *data)
{
	int	i;

	i = 0;
	if (data->env_exists == false)
		return ;
	if (env[i] == NULL)
	{
		ft_create_empty_env(&data->env_tesh);
	}
	while (env[i])
	{
		ft_create_env_lst(&data->env_tesh, env[i]);
		i++;
	}
	data->env_exists = true;
}
