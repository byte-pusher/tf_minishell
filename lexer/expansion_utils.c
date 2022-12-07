/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:02:09 by rkoop             #+#    #+#             */
/*   Updated: 2022/12/07 17:56:21 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"
int	get_var_amount(char *token_name)
{
	int i;
	int count;
	
	i = 0;
	count = 0;
	// printf("%s\n", token_name);
	while(token_name[i] != '\0')
	{
		if (token_name[i] == '$')
			count++;
		i++;
	}
	return (count);
}

int get_var_len(char *env_var)
{
	int i;

	i = 0;
	while (env_var[i] != '=')
		i++;
	return (i);
}

void	ft_str_remove(char *str, const char *sub)
{
	// ptr to start of part to be removed
	char *start = ft_strnstr(str, sub, ft_strlen(str));
	// ptr to end
	char *end = start + ft_strlen(sub);
	// concecnate: copy end part to start part
	ft_strncpy(start, end, ft_strlen(str));
}

void	free_var_arr(char **var_arr)
{
	int i;

	i = 0;
	while (var_arr[i] != NULL)
	{
		free(var_arr[i]);
		i++;
	}
	free(var_arr[i]);
	free(var_arr);
}
