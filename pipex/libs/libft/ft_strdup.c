/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:00:09 by gjupy             #+#    #+#             */
/*   Updated: 2022/05/05 14:42:18 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// if (!s1) original strdup give segv and not NULL

char	*ft_strdup(const char *s1)
{
	const char	*s2;
	int			len;

	len = ft_strlen(s1);
	s2 = malloc(len + 1);
	if (s2 == NULL)
		return (NULL);
	ft_strlcpy((char *)s2, (char *)s1, (len + 1));
	return ((char *)s2);
}
