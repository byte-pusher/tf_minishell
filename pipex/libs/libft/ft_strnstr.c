/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 20:21:12 by gjupy             #+#    #+#             */
/*   Updated: 2022/04/19 17:20:09 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// line 28: if the needle in the position the pointer 
// is pointing is found there, return haystack

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = len;
	if (*needle == '\0')
		return ((char *)haystack);
	while (*haystack && len--)
	{
		if ((!ft_strncmp(haystack, needle, ft_strlen(needle))))
		{
			if ((i + ft_strlen(needle)) <= j)
				return ((char *)haystack);
		}
		haystack++;
		i++;
	}
	return (NULL);
}
