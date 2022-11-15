/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 20:08:57 by gjupy             #+#    #+#             */
/*   Updated: 2022/04/08 20:08:57 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;
	char	*st;

	st = (char *) s;
	len = ft_strlen(st) + 1;
	st += len - 1;
	while (len--)
	{
		if ((char)c == *st)
			return (st);
		st--;
	}
	return (NULL);
}
