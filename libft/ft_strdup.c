/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:32:56 by rkoop             #+#    #+#             */
/*   Updated: 2022/04/17 15:36:34 by rkoop            ###   ########.fr       */
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
