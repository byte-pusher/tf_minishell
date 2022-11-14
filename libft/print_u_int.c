/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_u_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:12:14 by rkoop             #+#    #+#             */
/*   Updated: 2022/08/13 12:22:15 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static void	ft_putnbr_u(unsigned int n, int fd)
{
	long long int	t;

	t = n;
	if (t > 9)
	{
		ft_putnbr_u((t / 10), fd);
		ft_putchar_fd((t % 10 + '0'), fd);
	}
	else
		ft_putchar_fd((t + '0'), fd);
}

int	print_u_int(unsigned int arg)
{
	ft_putnbr_u(arg, 1);
	return (count_digits_u(arg));
}
