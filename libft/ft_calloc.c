/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 17:11:38 by rkoop             #+#    #+#             */
/*   Updated: 2022/04/17 18:29:31 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
#include<stdint.h>

void	*ft_calloc(unsigned int count, size_t size)
{
	unsigned int	area;
	char			*rtr_ptr;

	if (size && SIZE_MAX / size < count)
		return (NULL);
	area = count * size;
	rtr_ptr = malloc(area);
	if (rtr_ptr == NULL)
		return (NULL);
	ft_bzero(rtr_ptr, area);
	return ((void *)rtr_ptr);
}
