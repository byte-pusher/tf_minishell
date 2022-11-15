/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 19:27:07 by gjupy             #+#    #+#             */
/*   Updated: 2022/04/19 17:18:57 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1t;
	unsigned char	*s2t;

	s1t = (unsigned char *) s1;
	s2t = (unsigned char *) s2;
	if (n == 0)
		return (0);
	i = 0;
	while (i < n - 1)
	{
		if (s1t[i] == s2t[i])
			i++;
		else
			break ;
	}
	return (s1t[i] - s2t[i]);
}
