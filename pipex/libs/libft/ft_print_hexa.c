/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 12:51:05 by gjupy             #+#    #+#             */
/*   Updated: 2022/06/03 15:56:11 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_flags(int flags, int c)
{
	if (flags == hash)
	{
		if (c == 'x')
			return (ft_print_str("0x"));
		return (ft_print_str("0X"));
	}
	return (0);
}

static int	ft_lower_or_upper(int c)
{
	if (c == 'x')
		return (1);
	return (0);
}

int	ft_print_hexa(unsigned int n, int c, int flags)
{
	int				i;
	int				j;
	char			s[8];
	char			*hex;

	i = 0;
	if (n == 0)
		return (ft_print_char('0'));
	j = ft_check_flags(flags, c);
	if (ft_lower_or_upper(c))
		hex = "0123456789abcdef";
	else
		hex = "0123456789ABCDEF";
	while (n)
	{
		s[i++] = hex[n % 16];
		n /= 16;
	}
	while (--i >= 0)
		j += ft_print_char(s[i]);
	return (j);
}
