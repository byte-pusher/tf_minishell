/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 18:44:22 by rkoop             #+#    #+#             */
/*   Updated: 2022/08/13 12:22:06 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	print_ptr(unsigned long arg)
{
	int				hold;
	char			arr[18];
	int				i;
	int				c;

	i = 0;
	if ((void *)arg == NULL)
	{
		ft_putstr_fd("0x0", 1);
		return (i + 3);
	}
	while (arg != 0)
	{
		hold = arg % 16;
		if (hold < 10)
			arr[i++] = hold + 48;
		else
			arr[i++] = hold + 87;
		arg = arg / 16;
	}
	c = i - 1;
	ft_putstr_fd("0x", 1);
	while (c >= 0)
		ft_putchar_fd(arr[c--], 1);
	return (i + 2);
}
