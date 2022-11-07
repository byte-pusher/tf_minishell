/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:25:44 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/07 21:31:10 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/lexer.h"

t_token	*ft_lstlast(t_token *lst)
{
	t_token	*p;

	if (lst == NULL)
		return (NULL);
	p = lst;
	while (p->next)
		p = p->next;
	return (p);
}

void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*p;

	if (lst && new)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			p = ft_lstlast(*(lst));
			p->next = new;
			new->prev = p;
		}
	}
}

t_token	*ft_lstnew(t_token **tokens)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (node == NULL)
		exit(-1);					// create here exit_failure funciton to free the tokens list
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

bool	ft_is_space(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (true);
	return (false);
}

int	ft_get_chartype(char c)
{
	if (c == '|')
		return (PIPE);
	if (c == '>')
		return (GREAT);
	if (c == '<')
		return (LESS);
	if (c == '\'')
		return (SQUOTE);
	if (c == '\"')
		return (DQUOTE);
	return (COMMAND);
}

void	ft_handle_cmd(t_data *data, int *i, int type)
{
	int		start;
	int		len;
	t_token *new_token;

	start = *i;
	new_token = ft_lstnew(&data->tokens);
	new_token->type = type;
	while (data->input[*i] != ' '
			&& ft_get_chartype(data->input[*i]) == COMMAND)
	{
		
		(*i)++;
	}
	dprintf(2, "jo\n");
	len = *i - 1 - start;
	printf("%d\n", len);
	new_token->name = ft_substr(data->input, start, len);
	ft_lstadd_back(&data->tokens, new_token);
}

void	ft_handle_redirections(t_data *data)
{

}

void	ft_handle_quotes(t_data *data)
{

}

void	ft_lexer(t_data *data)
{
	int	i;
	int	type;

	i = 0;
	while (data->input[i])
	{
		while (ft_is_space(data->input[i]) == true)
			i++;
		type = ft_get_chartype(data->input[i]);
		if (type == COMMAND)
			ft_handle_cmd(data, &i, type);
		else if (type == GREAT || type == LESS)
			ft_handle_redirections(data);
		else if(type == SQUOTE || type == DQUOTE)
			ft_handle_quotes(data);
		i++;
	}
}
// ls -a | wc -l