/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:41:25 by gjupy             #+#    #+#             */
/*   Updated: 2022/05/05 14:51:14 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_set_flags(int c, const char **format)
{
	int	f;

	f = 0;
	if (c == '#')
	{
		c = *(++(*format));
		return (hash);
	}
	else if (c == ' ' || c == '+')
	{
		while (**format == ' ' || **format == '+')
		{
			if (**format == '+')
				f = 1;
			c = *(++(*format));
		}
		if (f)
			return (plus);
		return (space);
	}
	return (0);
}

static int	ft_eval_format(char c, va_list args, const char **format)
{
	int	flags;

	flags = ft_set_flags(c, format);
	if (flags)
		c = **format;
	if (c == '%')
		return (ft_print_char('%'));
	if (c == 'c')
		return (ft_print_char(va_arg(args, int)));
	if (c == 's')
		return (ft_print_str(va_arg(args, const char *)));
	if (c == 'd' || c == 'i')
		return (ft_print_int(va_arg(args, int), flags));
	if (c == 'u')
		return (ft_print_uint(va_arg(args, unsigned int)));
	if ((c == 'x' || c == 'X'))
		return (ft_print_hexa(va_arg(args, unsigned int), c, flags));
	if (c == 'p')
		return (ft_print_ptr((unsigned long)va_arg(args, void *)));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	int		ret;
	va_list	args;

	va_start(args, format);
	ret = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			ret += ft_eval_format(*format, args, &format);
		}
		else
			ret += ft_print_char(*format);
		format++;
	}
	va_end(args);
	return (ret);
}
