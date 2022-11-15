/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 19:06:37 by gjupy             #+#    #+#             */
/*   Updated: 2022/04/19 17:18:34 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	ct;
	unsigned char	*st;

	ct = (unsigned char) c;
	st = (unsigned char *) s;
	while (n--)
	{
		if (*st == ct)
			return (st);
		st++;
	}
	return (NULL);
}
