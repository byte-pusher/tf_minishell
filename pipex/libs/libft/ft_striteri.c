/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 17:58:42 by gjupy             #+#    #+#             */
/*   Updated: 2022/05/05 14:42:30 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;
	unsigned int	j;

	if (s == NULL || f == NULL)
		return ;
	i = 0;
	j = ft_strlen(s);
	while (i < j)
	{
		(*f)(i, s);
		i++;
		s++;
	}
}
