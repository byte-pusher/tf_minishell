/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 19:46:59 by gjupy             #+#    #+#             */
/*   Updated: 2022/06/03 16:05:46 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_put_uint_fd(unsigned int n, int fd)
{
	char	c;

	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	if (n >= 10)
		ft_putnbr_fd(n / 10, fd);
	c = (n % 10) + '0';
	write(fd, &c, 1);
}

static int	ft_count_digits_uint(unsigned int n)
{
	unsigned int	count;

	count = 0;
	if (!n)
		count = 1;
	while (n)
	{
		count++;
		n /= 10;
	}
	return ((int)count);
}

int	ft_print_uint(unsigned int u)
{
	ft_put_uint_fd(u, 1);
	return (ft_count_digits_uint(u));
}
