#include "../includes/shell.h"
#include <string.h>
#include <stdio.h>

// current problem: long expansion after short one in same cmd 
char *get_var(t_data *data, char *var)
{
	t_env	*current_env;
	char 	*value;
	size_t 	len_var;

	len_var = ft_strlen(var);
	current_env = data->env_tesh;
	value = NULL;
	
	// $$ -> return??

	// $? -> exit_status of last command
	if (ft_strncmp("?", var + 1, get_var_len(current_env->var)) == 0)
		return(ft_itoa(exit_status));
	while (current_env != NULL)
	{
		// check if given var is in current list elem->var. ! additional check for case, char *var is empty
		if (ft_strncmp(current_env->var, var + 1, get_var_len(current_env->var)) == 0)
		{
			dprintf(2, "\n current env var: %s", current_env->var);
			dprintf(2, "\n var %s", var + 1);
			value = malloc(sizeof(char) * ((ft_strlen(current_env->var) - len_var)));
			if (value == NULL)
				exit(ENOMEM);
			// copy var string starting at strt to value
			value = ft_substr(current_env->var, len_var, ft_strlen(current_env->var) - len_var);
			break;
		}
		current_env = current_env->next;
	}
	return (value);
}

void insert_value(t_token *token, char *var, char *value, int start_index)
{
	// lens as variables to avoid multiple strlen calls
	size_t len_token_name;
	size_t len_value;

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
	// copy first strA until start to new strC, nullterminate
	ft_strlcpy(name_expanded, token->name, start_index + 1);
	// strlcat to copy strB
	ft_strlcat(name_expanded, value, (len_token_name + len_value));
	// strlcat to copy rest of strB (strcC, strA + x)
	ft_strlcat(name_expanded, token->name + start_index, (len_token_name + len_value));
	// free & replace token name with extended str
	free(token->name);
	token->name = name_expanded;
}





void expand_tokens(t_data *data, t_token *token)
{
	char *var;
	char *value;
	int i;
	int j;
	int start;
	int end;
	int start_index;

	i = 0;
	j = 0;
	start = 0;
	end = 0;
	var = NULL;
	value = NULL;
	start_index = 0;
	var = malloc(sizeof(char) * 5);

	while (token->name[i] != '\0')
	{
		if (token->name[i] == '$')
		{
			start = i;
			while (token->name[i] != ' ' && token->name[i] != '\0')
				i++;
			end = i;
			var = (char *)realloc(var, sizeof(char) * (end - start));
			if (var == NULL)
				exit(ENOMEM);
			start_index = start;
			//do ine cternal function?
			while (start < end)
			{
				var[j] = token->name[start];
				j++;
				start++;
			}
			j = 0;
			// look up variable in ENV
			value = get_var(data, var);
			if (value != NULL)
			{
				insert_value(token, var, value, start_index);
				free(value);
			}
			else
				ft_str_remove(token->name, var);
			dprintf(2, "\n token name: %s", token->name);
			dprintf(2, "\n -----------\n");
		
		}
		i++;
	}
	if (var != NULL)
		free(var);
}

void expansion(t_data *data)
{
	t_token *current_token;

	current_token = data->tokens;
	while (current_token != NULL)
	{
		if (current_token->type == DQUOTE || current_token->type == COMMAND)
			expand_tokens(data, current_token);
		current_token = current_token->next;
	}
}
