/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 21:43:24 by rkoop             #+#    #+#             */
/*   Updated: 2022/11/30 20:46:10 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	ft_pwd(void)
{
	char *buffer;
	
	buffer = NULL;
	printf("%s\n",getcwd(buffer, 0));
	free(buffer);
}
