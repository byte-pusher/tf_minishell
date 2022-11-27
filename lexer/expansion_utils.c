/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:02:09 by rkoop             #+#    #+#             */
/*   Updated: 2022/11/27 18:02:58 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int get_var_len(char *env_var)
{
	int i;

	i = 0;
	while (env_var[i] != '=')
		i++;
	return (i);
}

void *ft_str_remove(char *str, const char *sub)
{
	// ptr to start of part to be removed
	char *start = ft_strnstr(str, sub, ft_strlen(str));
	// ptr to end
	char *end = start + ft_strlen(sub);
	// concecnate: copy end part to start part
	ft_strncpy(start, end, ft_strlen(str));
}
