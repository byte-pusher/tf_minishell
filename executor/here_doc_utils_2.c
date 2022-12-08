/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 17:13:43 by gjupy             #+#    #+#             */
/*   Updated: 2022/12/08 14:11:36 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

bool	ft_is_var(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i + 1] && s[i] == '$' && ft_is_space(s[i + 1]) == false)
			return (true);
		i++;	
	}
	return (false);
}

char	*get_var_hd(char *var, t_data *data)
{
	t_env	*current_env;
	size_t	len_current_env_var;
	size_t	len_var;
	int		i;

	current_env = ft_lstfirst_env(&data->env_tesh);
	len_current_env_var = 0;
	len_var = ft_strlen(var);
	i = 0;
	// $  -> stays as $
	// $$ -> bash: return of current pid. 	NOT IN SUBJECT.
	if (ft_strncmp("$", var, 1) == 0 && len_var == 1 ||
		ft_strncmp("$$", var, 2) == 0 && len_var == 2)
		return (var+1);
	// $? -> g_exit_status of last command, from subject: "the exit status of the most recently executed foreground pipeline"
	if (ft_strncmp("?", var + 1, get_var_len(current_env->var)) == 0)
		return (ft_itoa(g_exit_status));
	while (current_env != NULL)
	{
		len_current_env_var = get_var_len(current_env->var);
		// check if given var is in current list elem->var. ! additional check for case, char *var is empty
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

void	insert_value_hd(t_heredoc *heredoc, char *read_sub, char *value, int start_index)
{
	// lens as variables to avoid multiple strlen calls
	size_t	len_token_name;
	size_t	len_value;
	char	*new_read;

	len_token_name = ft_strlen(heredoc->read);
	len_value = ft_strlen(value) + 1;
	ft_str_remove(heredoc->read, read_sub);
	new_read = malloc(sizeof(char) * (len_token_name + len_value));
	if (new_read == NULL)
		exit(ENOMEM);
	ft_strlcpy(new_read, heredoc->read, start_index + 1);
	ft_strlcat(new_read, value, (len_token_name + len_value));
	ft_strlcat(new_read, heredoc->read + start_index, (len_token_name + len_value));
	if (heredoc->read != NULL)
	{
		free(heredoc->read);
		heredoc->read = ft_strdup(new_read);
	}
	free(new_read);
}

void	ft_expand_read(t_heredoc *heredoc, t_data *data)
{
	char	*new_read;
	char	*value;
	int		i;
	int		start;
	int		end;
	int		str_counter;
	char	**read_sub_arr;

	i = 0;
	start = 0;
	end = 0;
	// value = NULL;
	str_counter = 0;
	int	var_amount = get_var_amount(heredoc->read);
	read_sub_arr = (char **)malloc(sizeof(char *) * (var_amount + 1));
	while (heredoc->read[i] != '\0')
	{
		if (heredoc->read[i] == '$')
		{
			var_amount--;
			start = i;
			i++;
			while (heredoc->read[i] != ' ' && heredoc->read[i] != '\0' && heredoc->read[i] != '$'
					&& heredoc->read[i] != '\"' && heredoc->read[i] != '\'')
				i++;
			end = i;
			read_sub_arr[str_counter] = ft_substr(heredoc->read, start, end - start);
			if (read_sub_arr[str_counter] == NULL)
				exit(ENOMEM);
			value = get_var_hd(read_sub_arr[str_counter], data);
			if (value != NULL)
				insert_value_hd(heredoc, read_sub_arr[str_counter], value, start);
			else
				ft_str_remove(heredoc->read, read_sub_arr[str_counter]);
			str_counter++;
			if (var_amount)
			{
				i = start;
				continue;
			}
		}
		i++;
	}
	read_sub_arr[str_counter] = NULL;
	ft_free_strings(&read_sub_arr);
}
