/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 21:43:24 by rkoop             #+#    #+#             */
/*   Updated: 2022/12/12 22:32:28 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	ft_pwd(void)
{
	char	*buffer;
	char	*path_name;

	buffer = NULL;
	path_name = getcwd(buffer, 0);
	printf("%s\n", path_name);
	free(buffer);
	free(path_name);
}
