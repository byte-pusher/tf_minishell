/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 13:33:45 by rkoop             #+#    #+#             */
/*   Updated: 2022/08/13 12:21:40 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	check_set(char a, char const *set)
{
	unsigned int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == a)
			return (0);
		i++;
	}
	return (1);
}

static int	get_flag(char const *s, int i)
{
	int	flag;

	flag = 0;
	while ((check_set(s[i], "# +") == 0))
	{
		if (s[i] == ' ' && flag != plus)
				flag = space;
		if (s[i] == '#')
			flag = hash;
		if (s[i] == '+')
			flag = plus;
		i++;
	}
	return (flag);
}

static int	get_flag_len(char const *s, int i)
{
	int	len;

	len = 0;
	while (check_set(s[i], "# +") == 0)
	{
		len++;
		i++;
	}
	return (len);
}

static int	get_format(const char c, va_list args, int flag)
{
	int	print_len;

	print_len = 0;
	if (c == 'i' || c == 'd')
		print_len = print_int(va_arg(args, int), flag);
	if (c == 'u')
		print_len = print_u_int(va_arg(args, unsigned int));
	if (c == 'c')
		print_len = print_char(va_arg(args, int));
	if (c == 's')
		print_len = print_str(va_arg(args, void *));
	if (c == '%')
	{
		ft_putchar_fd('%', 1);
		print_len = 1;
	}
	if (c == 'p')
		print_len = print_ptr(va_arg(args, unsigned long));
	if (c == 'X' || c == 'x')
		print_len = print_hexa(va_arg(args, unsigned int), c, flag);
	return (print_len);
}

int	ft_printf(const char *s, ...)
{
	int		i;
	int		len;
	int		flag;
	va_list	args;

	i = 0;
	len = 0;
	flag = 0;
	va_start(args, s);
	while (s[i])
	{
		if (s[i] == '%' && (check_set(s[i + 1], "cspdiuxX%# +") == 0))
		{
			flag = get_flag((char *)s, i + 1);
			i = i + get_flag_len((char *)s, i + 1);
			i++;
			len = len + get_format(s[i], args, flag);
			flag = 0;
		}
		else
			len = len + print_char(s[i]);
		i++;
	}
	va_end(args);
	return (len);
}
