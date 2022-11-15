/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:58:52 by gjupy             #+#    #+#             */
/*   Updated: 2022/04/19 17:19:56 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// full size of buffer ('\0' included)
// appends src to the end of dst
// at most size - len dst - 1
// NULL terminates the result
// returns initial len dst + len src
// dst size is the dst + smthg. So if the dstsize is <= 
// we can't add anything else

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dst_len >= dstsize)
		return (src_len + dstsize);
	i = 0;
	while (src[i] && i + dst_len < dstsize - 1)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}
