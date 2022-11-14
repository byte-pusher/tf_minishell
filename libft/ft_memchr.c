/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 12:46:50 by rkoop             #+#    #+#             */
/*   Updated: 2022/04/14 13:35:07 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	charc;
	unsigned int	i;

	str = (unsigned char *)s;
	charc = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (str[i] == charc)
		{
			return (str + i);
		}
		i++;
	}
	return (NULL);
}
