/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:55:37 by rkoop             #+#    #+#             */
/*   Updated: 2022/12/08 14:16:53 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"
#include <string.h>
#include <stdio.h>

//fts neede
//1. check if var exists: check for hidden and visible
//2. get amount of vars in one token
//3. get var len
//4. check if is var declaration
//5. free creatd var array




int	exp_var_exists(char *cmd_arg, t_env *env_tesh)
{
	t_env	*current_env;
	int		var_len;

	current_env = env_tesh;
	var_len = comp_var_len(cmd_arg);
	while (current_env != NULL)
	{
		if (current_env->hidden == false)
		{
			if (ft_strncmp(current_env->var, cmd_arg, var_len) == 0)
				return (0);
		}
		else if (current_env->hidden == true)
		{
			if (ft_strncmp(current_env->var, cmd_arg, ft_strlen(cmd_arg) == 0))
				return (0);
		}
		current_env = current_env->next;
	}
	return (1);
}

//get len until =


char	*get_var(t_data *data, char *var)
{
	t_env	*current_env;
	size_t	len_current_env_var;
	size_t	len_var;
	int		i;

	current_env = data->env_tesh;
	len_current_env_var = 0;
	len_var = ft_strlen(var);
	i = 0;
	if (ft_strncmp("$", var, 1) == 0 && len_var == 1)
		return (var);
	if (ft_strncmp("$$", var, 2) == 0 && len_var == 2)
		return (var + 1);
	if (ft_strncmp("?", var + 1, get_var_len(current_env->var)) == 0)
		return (ft_itoa(g_exit_status));
	while (current_env != NULL)
	{
		len_current_env_var = get_var_len(current_env->var);
		if (ft_strncmp(current_env->var, var + 1, len_current_env_var) == 0
			&& var[len_current_env_var + 1] == '\0')
		{
			while (current_env->var[i] != '=')
				i++;
			return (current_env->var + ft_strlen(var));
		}
		current_env = current_env->next;
	}
	return (NULL);
}

void	insert_value(t_token *token, char *var, char *value, int start_index)
{
	// lens as variables to avoid multiple strlen calls
	size_t	len_token_name;
	size_t	len_value;

	len_token_name = ft_strlen(token->name);
	//+1 cause of $ in beginng
	len_value = ft_strlen(value) + 1;
	// remove $var from token->name
	ft_str_remove(token->name, var);
	// second: insert value
	// allocate new string for concenated one
	char *name_expanded = malloc(sizeof(char) * (len_token_name + len_value));
	if (name_expanded == NULL)
		exit(ENOMEM);
	// copy first strA until start to new strC
	ft_strlcpy(name_expanded, token->name, start_index + 1);
	// strlcat to copy strB
	ft_strlcat(name_expanded, value, (len_token_name + len_value));
	// strlcat to copy rest of strB (strcC, strA + x)
	ft_strlcat(name_expanded, token->name + start_index, (len_token_name + len_value));
	// free & replace token name with extended str
	//dprintf(2, "\ntoken name %s\n", token->name);
	if (token->name != NULL)
	{
		free(token->name);
		token->name = ft_strtrim(name_expanded, "\"");
	}
	free(name_expanded);
}

void	expand_tokens(t_data *data, t_token *token)
{
	char	*value;
	int		i;
	int		j;
	int		start;
	int		end;
	int		start_index;
	int		str_counter;
	char	**var_arr;

	i = 0;
	j = 0;
	start = 0;
	end = 0;
	value = NULL;
	start_index = 0;
	str_counter = 0;
	var_arr = (char **)malloc(sizeof(char *) * (get_var_amount(token->name) + 1));
	while (token->name[i] != '\0')
	{
		if (token->name[i] == '$' || ((token->name[i] == '\'' && token->name[i + 1] == '$')))
		{
			if (token->name[i] == '\'' && token->name[i + 1] == '$')
			{
				i++;
				start = i;
				//dprintf(2, "char %c", token->name[i]);
				while (token->name[i] != '\'' && token->name[i] != '\0' && token->name[i] != ' ')
				{
					i++;
					if (token->name[i] == '$')
						break ;
				}
					
			}
			else
			{
				start = i;
				i++;
				while (token->name[i] != ' ' && token->name[i] != '\0' && token->name[i] != '\"' && token->name[i] != '$' && token->name[i] != '\'' )
					i++;

			}
			end = i;
			var_arr[str_counter] = malloc(sizeof(char) * (end - start) + 1);
			if (var_arr[str_counter]  == NULL)
				exit(ENOMEM);
			start_index = start;
			
			while (start < end)
			{
				var_arr[str_counter][j] = token->name[start];
				j++;
				start++;
			}
			var_arr[str_counter][j] = '\0';
			j = 0;
			// look up variable in ENV
			//dprintf(2, "\nvar: %s", var_arr[str_counter]);
			value = get_var(data, var_arr[str_counter]);
			//dprintf(2, "\nvalue: %s", value);
			if (value != NULL)
			{
				insert_value(token, var_arr[str_counter], value, start_index);
			}
			// else if (token->type != DQUOTE && exp_var_exists(var_arr[str_counter], data->env_tesh) == 0)
			// {
			// 	ft_str_remove(token->name, var_arr[str_counter]);
			// 	dprintf(2,"\ndeleting\n");
			// }
			else
				ft_str_remove(token->name, var_arr[str_counter]);
			//dprintf(2,"\ntoken type:%i", token->type);	
			str_counter++;
		}
		i++;
	}
	var_arr[str_counter] = NULL;
	//use free strings?
	free_var_arr(var_arr);
}

void	expansion(t_data *data)
{
	t_token	*current_token;

	current_token = data->tokens;
	while (current_token != NULL)
	{
		if (current_token->type == DQUOTE || current_token->type == COMMAND)
		{
			if (current_token->prev != NULL
				&& current_token->prev->type == LESSLESS)
			{
				current_token = current_token->next;
				continue ;
			}
			expand_tokens(data, current_token);
		}
		current_token = current_token->next;
	}
}