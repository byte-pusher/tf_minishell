#include "../includes/shell.h"
#include <string.h>
#include <stdio.h>

// current problem: long expansion after short one in same cmd 
//ideas: external function for var creaion from string
//replacement of realloc necessary! 
//check execution style of builtins and returns


char *get_var(t_data *data, char *var)
{
	t_env	*current_env;
	size_t	len_current_env_var;
	size_t 	len_var;
	int		i;

	current_env = data->env_tesh;
	len_current_env_var = 0;
	len_var = ft_strlen(var);
	i = 0;
	
	// $  -> stays as $
	// $$ -> bash: return of current pid. 	NOT IN SUBJECT.
	if (ft_strncmp("$", var, 1) == 0 && len_var == 1 || ft_strncmp("$$", var, 2) == 0 && len_var == 2)
		return(var+1);
	// $? -> exit_status of last command, from subject: "the exit status of the most recently executed foreground pipeline"
	if (ft_strncmp("?", var + 1, get_var_len(current_env->var)) == 0)
		return(ft_itoa(exit_status));
	while (current_env != NULL)
	{
		len_current_env_var = get_var_len(current_env->var);
		// check if given var is in current list elem->var. ! additional check for case, char *var is empty
		if (ft_strncmp(current_env->var, var + 1, len_current_env_var) == 0 && var[len_current_env_var + 1] == '\0')
		{
			while(current_env->var[i] != '=')
				i++;
			return(current_env->var + ft_strlen(var));
		}
		current_env = current_env->next;
	}
	return(NULL);
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
				insert_value(token, var, value, start_index);
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
