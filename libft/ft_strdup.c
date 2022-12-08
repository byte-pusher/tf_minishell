/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:32:56 by rkoop             #+#    #+#             */
/*   Updated: 2022/12/08 14:02:51 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strdup(const char *s1)
{
	size_t				i;
	unsigned int		area;
	char				*dst;

	i = 0;
	area = (ft_strlen(s1) + 1) * sizeof(char);
	dst = malloc(area);
	if (dst == NULL)
		return (NULL);
	while (s1[i] && s1[i] != '\0' && i <= ft_strlen(s1))
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
