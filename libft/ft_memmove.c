/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:37:33 by rkoop             #+#    #+#             */
/*   Updated: 2022/04/17 20:07:20 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*h_dst;
	unsigned char	*h_src;

	h_dst = (unsigned char *)dst;
	h_src = (unsigned char *)src;
	if (!h_dst || !h_src || len == 0)
		return (dst);
	if (h_dst >= h_src)
	{
		while (len > 0)
		{
			h_dst[len - 1] = h_src[len - 1];
			len--;
		}
	}
	else
		ft_memcpy(h_dst, h_src, len);
	return (dst);
}
