#include "../includes/shell.h"


//check if quotes are left open in input
//mixed  cases: "a"'"b'" || 'a'"'b"'
int		check_quotes(char *str)
{
	unsigned int	i;
	unsigned int	status;
	
	status = NON;
	i = 0;
	while(str[i] != '\0')
	{
		if (str[i] == '\"')
		{
			status = DOUBLE_OPEN;
			i++;
			while (str[i] != '\0' && status == DOUBLE_OPEN)
			{
				if(str[i] == '\"')
					status = DOUBLE_CLOSED;
				else
					i++;
			}	
		}
		if (str[i] == '\'')
		{
			status = SINGLE_OPEN;
			i++;
			while (str[i] != '\0' && status == SINGLE_OPEN)
			{
				if(str[i] == '\'')
					status = SINGLE_CLOSED;
				else	
					i++;
			}	
		}
		i++;
	}
	if (status == SINGLE_OPEN || status == DOUBLE_OPEN)
		status = OPEN;
	return(status);
}

// //expansion of variables within DQUOTES
// // $? -> exit_status of last command
// // $$ -> just $
// char	*get_var(t_data *data, char *var, int start)
// {
// 	t_env 	*current;
// 	char	*value;
// 	int		i;

// 	current = data->env_tesh;
// 	value = NULL;
// 	i = 0;

// 	while (current != NULL)
// 	{
// 		//check if given var is in current list elem->var. ! additional check for case, char *var is empty
// 		if (ft_strnstr(current->var, var, ft_strlen(current->var)) != NULL)
// 		{
// 			while (current->var[i] != '=')
// 				i++;
// 			value = malloc(sizeof(char) * (ft_strlen(current->var) - start));
// 			if (value == NULL)
// 				exit(ENOMEM);
// 			//copy var string starting at strt to value
// 			value = ft_substr(current->var, start, ft_strlen(current->var) - start);
// 			break ;
// 		}
// 		current = current->next;
// 	}
// 	return (value);
// }

// void	insert_value(t_token *token, char *var, char *value, int start_index)
// {
// 	//first remove var from string
//     /* get pointer to start of string to be removed*/
//     char *start = ft_strnstr(token->name, var, ft_strlen(token->name));
//     /* get pointer to end of string to be removed*/
//     char *end = start + ft_strlen(var);
//     /* move rest of string to former start of string to be removed*/
//     ft_memmove(start, start + ft_strlen(var), ft_strlen(end) + 1);
	
// 	//second: insert value
// 	//create new strC for combined one
// 	char *name_expanded = malloc(sizeof(char) * (ft_strlen(start) + ft_strlen(value) + 1));
// 	if (name_expanded == NULL)
// 		exit(ENOMEM);
// 	//copy first strA until start to new strC, nullterminate
// 	ft_strlcpy(name_expanded, start, start_index);
// 	//strlcat to copy strB
// 	ft_strlcat(name_expanded, value, sizeof(name_expanded));
// 	//strlcat to copy rest of strB (strcC, strA + x)
// 	ft_strlcat(name_expanded, start + start_index, sizeof(name_expanded));
// 	//replace token name with extended str
// 	token->name = name_expanded;
// 	//free strings
// }

// void	expand_tokens(t_data *data, t_token *token)
// {
// 	char 	*var;
// 	char	*value;
// 	int 	i;
// 	int		j;
// 	int		start;
// 	int		end;
// 	int		start_index;

// 	i = 0;
// 	j = 0;
// 	start = 0;
// 	end = 0;
// 	var = NULL;
// 	value = NULL;
// 	start_index = 0;

// 	if (token->type == DQUOTE)
// 	{
// 		while (token->name[i] != '\0')
// 		{
// 			if (token->name[i] == '$')
// 			{
// 				start = i;
// 				while (token->name[i] != ' ' && token->name[i] != '\0')
// 					i++;
// 				end = i;
// 				var = malloc(sizeof(char) * (end - start));
// 				if (var == NULL)
// 					exit(ENOMEM);
// 				start_index = start;
// 				while(start <= end)
// 				{
// 					var[j] = token->name[start];
// 					j++;
// 					start++;
// 				}
// 				value = get_var(data, var, start_index);
// 				//modify token: insert value into token->name
// 				insert_value(token,var, value, start_index);
// 				free(var);
// 				free(value);
// 			}
// 			i++;
// 		}
// 	}
// }

// void	expansion(t_data *data)
// {
// 	t_token *current_token;

// 	current_token = data->tokens;
// 	while (current_token != NULL)
// 	{
// 		expand_tokens(data, current_token);
// 		current_token = current_token->next;
// 	}
// }
