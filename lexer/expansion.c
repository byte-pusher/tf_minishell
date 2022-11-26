# include "../includes/shell.h"
#include <string.h>
//expansion of variables within DQUOTES
// $? -> exit_status of last command
// $$ -> just $
char	*get_var(t_data *data, char *var)
{
	t_env 	*current_env;
	char	*value;

	current_env = data->env_tesh;
	value = NULL;
	while (current_env != NULL)
	{
		//check if given var is in current list elem->var. ! additional check for case, char *var is empty
		if (ft_strnstr(current_env->var, var + 1, ft_strlen(current_env->var)) != NULL)
		{
			value = malloc(sizeof(char) * ((ft_strlen(current_env->var) - ft_strlen(var))));
			if (value == NULL)
				exit(ENOMEM);
			//copy var string starting at strt to value
			value = ft_substr(current_env->var, ft_strlen(var), ft_strlen(current_env->var) - ft_strlen(var));
			break ;
		}
		current_env = current_env->next;
	}
	return (value);
}


// modify remove function to remove from start_index
char *str_remove(char *str, const char *sub) {
    char *p, *q, *r;
    if (*sub && (q = r = ft_strnstr(str, sub, ft_strlen(str))) != NULL) {
        size_t len = (size_t) ft_strlen(sub);
        while ((r = ft_strnstr(p = r + len, sub, ft_strlen(str))) != NULL) {
            while (p < r)
                *q++ = *p++;
        }
        while ((*q++ = *p++) != '\0')
            continue;
    }
    return str;
}

// char	ft_str_remove(char *str, char *substr, int start_index)
// {

// }

void	insert_value(t_token *token, char *var, char *value, int start_index)
{
	//remove $var from token->name
	str_remove(token->name, var);
	
	//second: insert value
	//allocate new string for concenated one
	char *name_expanded = malloc(sizeof(char) * (ft_strlen(token->name) + ft_strlen(value) + 1));
	if (name_expanded == NULL)
		exit(ENOMEM);
	//copy first strA until start to new strC, nullterminate
	ft_strlcpy(name_expanded, token->name, start_index + 1);
	//strlcat to copy strB
	ft_strlcat(name_expanded, value, (size_t)(ft_strlen(token->name) + ft_strlen(value) + 1));
	//strlcat to copy rest of strB (strcC, strA + x)
	ft_strlcat(name_expanded, token->name + start_index, (size_t)(ft_strlen(token->name) + ft_strlen(value) + 1));
	//free & replace token name with extended str
	free(token->name);
	token->name = name_expanded;
}

void	expand_tokens(t_data *data, t_token *token)
{
	char 	*var;
	char	*value;
	int 	i;
	int		j;
	int		start;
	int		end;
	int		start_index;

	i = 0;
	j = 0;
	start = 0;
	end = 0;
	var = NULL;
	value = NULL;
	start_index = 0;

	while (token->name[i] != '\0')
	{
		if (token->name[i] == '$')
		{
			//dprintf(2, "\n $ found");
			start = i;
			while (token->name[i] != ' ' && token->name[i] != '\0')
				i++;
			end = i;
			var = malloc(sizeof(char) * (end - start));
			if (var == NULL)
				exit(ENOMEM);
			start_index = start;
			dprintf(2, "\n var before: %s", var + 1);
			while(start < end)
			{
				var[j] = token->name[start];
				j++;
				start++;
			}
			j = 0;
			value = get_var(data, var);
			dprintf(2, "\n var from name: %s", var + 1);
			dprintf(2, "\n val from get_var: %s", value);
			//modify token: insert value into token->name
			insert_value(token, var, value, start_index);
			dprintf(2, "\n token name: %s", token->name);
			dprintf(2, "\n -----------\n");
			ft_memset(var, 0, ft_strlen(var));
			free(var);
			var = " ";
			free(value);
		}
		i++;
	}
}

void	expansion(t_data *data)
{
	t_token *current_token;

	current_token = data->tokens;
	while (current_token != NULL)
	{
		if (current_token->type == DQUOTE || current_token->type == COMMAND)
		{
			expand_tokens(data, current_token);
		}
		current_token = current_token->next;
	}
}
