/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 13:35:11 by gjupy             #+#    #+#             */
/*   Updated: 2022/04/18 22:53:46 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// allocates enough space for count objects that are size bytes of mem
// returns a pointer to the allocated memory
// the allocated memory is filled with bytes of values 0
// return: NULL pointer || pointer to alloc mem

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	if (size >= SIZE_MAX || count >= SIZE_MAX)
		return (NULL);
	p = malloc(size * count);
	if (!p)
		return (NULL);
	ft_bzero(p, (size * count));
	return (p);
}
