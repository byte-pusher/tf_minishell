/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 17:16:53 by gjupy             #+#    #+#             */
/*   Updated: 2022/05/05 14:42:50 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	int		size;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	s3 = malloc(size);
	if (s3 == NULL)
		return (NULL);
	ft_strlcpy(s3, (char *)s1, (ft_strlen(s1)) + 1);
	ft_strlcpy((s3 + ft_strlen(s1)), (char *) s2, (ft_strlen(s2) + 1));
	return (s3);
}
