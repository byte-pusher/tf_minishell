/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:25:44 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/21 17:49:49 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

bool	ft_is_file_name (t_token *new_token)
{
	if (new_token->prev != NULL
		&& (new_token->prev->type == GREAT
			|| new_token->prev->type == GREATGREAT || new_token->prev->type == LESS 
			|| new_token->prev->type == LESSLESS))
			return (true);
	return (false);
}

void	ft_cpy_string(t_data *data, t_token *new_token, int *i)
{
	int		start;
	int		end;

	start = *i;
	if (new_token->type == FILE_NAME)
	{
		while (data->input[*i] != '\0'
			&& ft_get_chartype(data->input, i) == GENERAL)
		{
			(*i)++;
			end = *i;
		}
	}
	else if (new_token->type == COMMAND)
	{
		while (data->input[*i] != '\0'
				&& (ft_get_chartype(data->input, i) == GENERAL
					|| ft_get_chartype(data->input, i) == WHITE_SPACE))
		{
			(*i)++;
			end = *i;
		}
	}
	(*i)--;
	new_token->name = ft_substr(data->input, start, end - start);
}

void	ft_handle_cmd(t_data *data, int *i, int type)
{
	t_token	*new_token;

	new_token = ms_lstnew(&data->tokens);
	ms_lstadd_back(&data->tokens, new_token);
	if (ft_is_file_name(new_token) == true)
		new_token->type = FILE_NAME;
	else
		new_token->type = COMMAND;
	ft_cpy_string(data, new_token, i);
}

void	ft_handle_heredoc_and_append(t_data *data, int *i, int type)
{
	t_token	*new_token;
	char	c;

	(*i)++;
	new_token = ms_lstnew(&data->tokens);
	new_token->type = type;
	new_token->name = malloc(3);
	if (type == LESSLESS)
		c = '<';
	else if (type == GREATGREAT)
		c = '>';
	new_token->name[0] = c;
	new_token->name[1] = c;
	new_token->name[2] = '\0';
	ms_lstadd_back(&data->tokens, new_token);
}

void	ft_handle_quotes(t_data *data, int *i, int type)
{
	if (type == SQUOTE)
		ft_handle_squote(data, i, type);
	else if (type == DQUOTE)
		ft_handle_dquote(data, i, type);
}

void	ft_handle_others(t_data *data, int type, char c)
{
	t_token	*new_token;

	new_token = ms_lstnew(&data->tokens);
	new_token->type = type;
	new_token->name = malloc(2);
	if (new_token->name == NULL)
		exit_status = MALLOC_ERR;
	new_token->name[0] = c;
	new_token->name[1] = '\0';
	ms_lstadd_back(&data->tokens, new_token);
}

int	ft_lexer(t_data *data)
{
	int	i;
	int	type;

	i = 0;
	while (data->input[i] != '\0')
	{
		while (ft_is_space(data->input[i]) == true)
			i++;
		type = ft_get_chartype(data->input, &i);
		if (type == GENERAL)
			ft_handle_cmd(data, &i, type);
		else if (type == LESSLESS || type == GREATGREAT)
			ft_handle_heredoc_and_append(data, &i, type);
		else if (type == SQUOTE || type == DQUOTE)
			ft_handle_quotes(data, &i, type);
		else if (type == PIPE || type == GREAT || type == LESS)
			ft_handle_others(data, type, data->input[i]);
		i++;
	}
	// ms_print_list(&data->tokens);
	return (SUCCESS);
}
