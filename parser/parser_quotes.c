

#include "../includes/shell.h"

//quote info necesary for expansions
//removal only after expansion possible
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



//for expansion
//add quoted/undquoted to every string token
//--> check which to expand
//expand on token base?
//to expand based on quotes
//strimtrim to remove quotes
//expand variables, check how to save if several words in quote


// $? -> exit_status of last command
// $$ -> just $


char	*get_var(t_data *data, char *var)
{
	t_env 	*current;
	char	*value

	current = data->env_tesh;
	value = NULL;

	while (current != NULL)
	{
		//check if given var is in current list elem->var. ! additional check for case, char *var is empty
		if (ft_strnstr(current->var != NULL))
		{
			while (current->var[i] != '=')
				i++;
			value = malloc(sizeof(char) * (ft_strlen(current->var) - start));
			//copy var string starting at strt to value
			value = ft_substr(current->var, start, ft_strlen(current->var) - start);
			break ;
		}
		current = current->next;
	}
	return (value);
}

void	insert_value(t_token *token, char *value, int start, int end)
{
	//first remove var from string


	//second: insert value
	//create new strC for combined one
	//how to replace best? new allocation necessary
	//copy first strA until start to new strC, nullterminate
	//strlcat to copy strB
	//strlcat to copy rest of strB (strcC, strA + x)

	//free strings
}

void	expand_tokens(t_data *data, t_token *token)
{
	char 	*var;
	char	*value;
	int 	i;
	int		j;
	int		start;
	int		end;

	i = 0;
	j = 0;
	start = 0;
	end = 0;
	var = NULL;
	value = NULL;

	if (token->type == DQUOTE)
	{
		while (token->name[i] != '\0')
		{
			if (token->name[i] == '$')
			{
				start = i;
				while (token->name[i] != ' ' && token->name[i] != '\0')
					i++;
				end = i;
				var = malloc(sizeof(char) * (end - start));
				while(start <= end)
				{
					var[j] = token->name[start];
					j++;
					start++;
				}
				value = get_var(data, var);
				//modify token: insert value into token->name
				insert_value(token, value, start);
				free(var);
				free(value);
			}
			i++;
		}
	}


}

void	expansion(t_data *data)
{
	t_token *current_token;

	current_token = data->tokens;

	while (current_token != NULL)
	{
		expand_tokens(data, current_token);
		current_token = tmp->next;
	}
	

}



