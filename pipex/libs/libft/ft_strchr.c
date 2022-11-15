/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:15:22 by gjupy             #+#    #+#             */
/*   Updated: 2022/05/05 14:42:07 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// + 1 to search fot the '/0'

char	*ft_strchr(const char *s, int c)
{
	int		len;
	char	*st;

	st = (char *) s;
	len = ft_strlen(st) + 1;
	while (len--)
	{
		if ((char)c == *st)
			return (st);
		st++;
	}
	return (NULL);
}
