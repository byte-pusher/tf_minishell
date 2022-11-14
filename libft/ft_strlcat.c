/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 18:16:56 by rkoop             #+#    #+#             */
/*   Updated: 2022/04/17 16:52:36 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	src_len;
	unsigned int	dst_len;
	unsigned int	max_len;

	i = 0;
	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	max_len = dstsize - dst_len - 1;
	if (dstsize == 0)
		return (src_len);
	if (dstsize < dst_len)
		return (dstsize + src_len);
	while (*dst)
		dst++;
	while (src[i] && i <= max_len && dst_len + i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst_len + src_len);
}
