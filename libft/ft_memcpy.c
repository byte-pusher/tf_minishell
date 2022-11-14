/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:19:30 by rkoop             #+#    #+#             */
/*   Updated: 2022/04/15 12:21:30 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*h_dst;
	char	*h_src;
	size_t	i;

	i = 0;
	if (dst == NULL || src == NULL)
		return (dst);
	h_dst = (char *)dst;
	h_src = (char *)src;
	while (i < n)
	{
		h_dst[i] = h_src[i];
		i++;
	}
	return (dst);
}
