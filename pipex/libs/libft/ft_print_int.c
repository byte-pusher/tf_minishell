/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 19:23:27 by gjupy             #+#    #+#             */
/*   Updated: 2022/06/03 15:31:06 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_digits_int(int n)
{
	unsigned int	count;

	count = 0;
	if (!n)
		count = 1;
	if (n < 0)
		n *= -1;
	while (n)
	{
		count++;
		n /= 10;
	}
	return ((int)count);
}

static int	ft_check_flags(int flags)
{
	if (flags == space)
		return (ft_print_char(' '));
	if (flags == plus)
		return (ft_print_char('+'));
	return (0);
}

int	ft_print_int(int i, int flags)
{
	int	j;

	j = 0;
	if (i >= 0)
		j = ft_check_flags(flags);
	ft_putnbr_fd(i, 1);
	if (i < 0)
		return (ft_count_digits_int(i) + 1);
	return (ft_count_digits_int(i) + j);
}
