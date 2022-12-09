/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_short.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:30:17 by rkoop             #+#    #+#             */
/*   Updated: 2022/12/08 18:03:34 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char	*get_value(t_data *data, char *var)
{
	t_env	*current_env;
	size_t	len_current_env_var;
	size_t	len_var;
	int		i;

	if (ft_lstfirst_env(&data->env_tesh)->var == NULL)
		return (NULL);
	current_env = data->env_tesh;
	len_var = ft_strlen(var);
	i = 0;
	if (ft_strncmp("$$", var, 2) == 0 && len_var == 2
		|| ft_strncmp("$", var, 1) == 0 && len_var == 1 )
		return ("$");
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

void	insert_value(t_token *token, char *var, char *value, int start)
{
	size_t	len_token_name;
	size_t	len_value;
	char	*name_expanded;

	name_expanded = NULL;
	len_token_name = ft_strlen(token->name);
	len_value = ft_strlen(value);
	ft_str_remove(token->name, var);
	name_expanded = malloc(sizeof(char) * (len_token_name + len_value));
	if (name_expanded == NULL)
		exit(ENOMEM);
	ft_strlcpy(name_expanded, token->name, start + 1);
	ft_strlcat(name_expanded, value, (len_token_name + len_value));
	ft_strlcat(name_expanded, token->name + start,
		(len_token_name + len_value));
	if (token->name != NULL)
	{
		free(token->name);
		token->name = ft_strtrim(name_expanded, "\"");
	}
	free(name_expanded);
}

//get var from string and replace in token->name
void	change_token_name(t_data *data, t_token *token, int start, int end)
{
	char	*variable;
	char	*value;

	variable = NULL;
	value = NULL;
	variable = malloc(sizeof(char) * (end - start) + 1);
	if (variable == NULL)
		exit(ENOMEM);
	variable = ft_substr(token->name, start, (end - start));
	value = get_value(data, variable);
	if (value != NULL)
		insert_value(token, variable, value, start);
	else
		ft_str_remove(token->name, variable);
}

//expand single token
void	expand_tokens(t_data *data, t_token *token)
{	
	int		i;
	int		start;
	int		end;

	i = 0;
	start = 0;
	end = 0;
	while (token->name[i] != '\0')
	{
		if (token->name[i] == '$' || ((token->name[i] == '\''
					&& token->name[i + 1] == '$')))
		{
			if (token->name[i] == '\'' && token->name[i + 1] == '$')
			{
				i++;
				start = i;
				while (token->name[i] != '\'' && token->name[i] != '\0'
					&& token->name[i] != ' ')
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
				while (token->name[i] != ' ' && token->name[i] != '\0'
					&& token->name[i] != '\"' && token->name[i] != '$'
					&& token->name[i] != '\'' )
					i++;
			}
			end = i;
			change_token_name(data, token, start, end);
		}
		i++;
	}
}

//main function looping through tokens
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
