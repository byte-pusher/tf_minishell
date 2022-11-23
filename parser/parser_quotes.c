

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


void	handle_quotes(t_data *data)
{
	if (check_quotes(data->input) != OPEN) 
	{
		ft_lstiter(data->tokens, expand_quotes);
		ft_lstiter(data->tokens, remove_quotes);
	}
		
}

