/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:56:56 by rkoop             #+#    #+#             */
/*   Updated: 2022/08/13 12:21:59 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	case_check(const char c)
{
	if (c == 'x')
		return (87);
	else
		return (55);
}

static int	flac_react(const char c, int flag)
{
	if (c == 'x' && flag == hash)
		ft_putstr_fd("0x", 1);
	else if (c == 'X' && flag == hash)
		ft_putstr_fd("0X", 1);
	if (flag == hash)
		return (2);
	return (0);
}

int	print_hexa(unsigned int arg, const char c, int flag)
{
	int				i;
	int				hold;
	int				count;
	char			*arr;

	i = 0;
	if (arg == 0)
		return (print_int(arg, 0));
	arr = malloc(count_digits_u(arg) * sizeof(char));
	while (arg != 0)
	{
		hold = arg % 16;
		if (hold < 10)
			arr[i++] = hold + 48;
		else
			arr[i++] = hold + case_check(c);
	arg = arg / 16;
	}
	count = i - 1;
	i = i + flac_react(c, flag);
	while (count >= 0)
		ft_putchar_fd(arr[count--], 1);
	free(arr);
	return (i);
}
