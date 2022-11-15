/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 17:21:27 by gjupy             #+#    #+#             */
/*   Updated: 2022/06/03 15:41:22 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_ptr(unsigned long p)
{
	int		i;
	char	s[16];
	char	*hex;
	int		j;

	hex = "0123456789abcdef";
	i = 0;
	j = 0;
	ft_print_str("0x");
	if (p == 0)
		return (ft_print_char('0') + 2);
	while (p)
	{
		s[i++] = hex[p % 16];
		p /= 16;
	}
	while (--i >= 0)
		j += ft_print_char(s[i]);
	return (j + 2);
}
