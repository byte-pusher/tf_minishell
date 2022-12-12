/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:02:09 by rkoop             #+#    #+#             */
/*   Updated: 2022/12/12 16:05:42 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	get_var_amount(char *token_name)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (token_name[i] != '\0')
	{
		if (token_name[i] == '$')
			count++;
		i++;
	}
	return (count);
}

int	get_var_len(char *env_var)
{
	int	i;

	i = 0;
	while (env_var[i] != '=')
		i++;
	return (i);
}

void	ft_str_remove(char *str, const char *sub)
{
	char	*start;
	char	*end;

	start = ft_strnstr(str, sub, ft_strlen(str));
	end = start + ft_strlen(sub);
	ft_strncpy(start, end, ft_strlen(str));
}

int	is_var_declaration(char *cmd_arg)
{
	int	i;

	i = 0;
	while (cmd_arg[i] != '\0')
	{
		if (cmd_arg[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

//move to other file
int	valid_export(char *cmd_arg)
{
	int	i;

	i = 0;
	while (cmd_arg[i] != '\0')
	{
		if (ft_isalpha(cmd_arg[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

int	comp_var_len(char *cmd_arg)
{
	int	i;

	i = 0;
	while (cmd_arg[i] != '\0')
	{
		if (cmd_arg[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

int	get_nr_of_vars(char *token_name)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (token_name[i] != '\0')
	{
		if (token_name[i] == '$')
			count++;
		i++;
	}
	return (count);
}

bool	ft_is_double_dollar(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1] == '$')
			return (true);
		i++;
	}
	return (false);
}

int		ft_get_next_var(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

void	ft_insert_dollars(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == 127)
			s[i] = '$';
		i++;
	}
}