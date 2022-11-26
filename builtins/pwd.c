/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 21:43:24 by rkoop             #+#    #+#             */
/*   Updated: 2022/11/26 21:57:38 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"


void	ft_pwd(t_data *data)
{
	char *current_dir;
	
	current_dir = malloc(sizeof(char) * (ft_strlen(get_var(data, "$PWD"))));
	printf("%s",getcwd(current_dir, sizeof(current_dir)));
	free(current_dir);
}

//return?