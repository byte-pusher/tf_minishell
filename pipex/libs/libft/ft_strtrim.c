/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 19:16:21 by gjupy             #+#    #+#             */
/*   Updated: 2022/05/05 14:44:03 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_charchr(char const *set, char c)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s2;
	int		i;
	int		j;
	int		size;

	if (s1 == NULL || set == NULL)
		return (NULL);
	i = 0;
	while (ft_charchr(set, s1[i]))
		i++;
	j = ft_strlen(s1) - 1;
	while (ft_charchr(set, s1[j]) && j > i)
		j--;
	size = j - i;
	s2 = ft_substr(s1, i, size + 1);
	return (s2);
}
