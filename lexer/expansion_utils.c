/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:02:09 by rkoop             #+#    #+#             */
/*   Updated: 2022/12/13 12:32:21 by rkoop            ###   ########.fr       */
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
