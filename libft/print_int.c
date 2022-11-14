/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 11:26:01 by rkoop             #+#    #+#             */
/*   Updated: 2022/08/13 12:22:03 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	print_int(int arg, int flag)
{
	if (arg < 0)
	{
		ft_putnbr_fd(arg, 1);
		return (count_digits(arg) + 1);
	}
	if (flag == plus)
	{
		ft_putchar_fd('+', 1);
		ft_putnbr_fd(arg, 1);
		return (count_digits(arg) + 1);
	}
	if (flag == space)
	{
		ft_putchar_fd(' ', 1);
		ft_putnbr_fd(arg, 1);
		return (count_digits(arg) + 1);
	}
	ft_putnbr_fd(arg, 1);
	return (count_digits(arg));
}
