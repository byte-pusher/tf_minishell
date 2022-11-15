/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_long.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 20:31:18 by gjupy             #+#    #+#             */
/*   Updated: 2022/06/24 22:56:09 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isspace(char c)
{
	return (c == 9 || c == 32 || c == '\t' || c == '\n'
		|| c == '\r' || c == '\v' || c == '\f');
}

long	ft_atoi_long(const char *str)
{
	long	i;
	int		digit;
	int		sign;

	sign = 1;
	while (isspace(*str))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	i = 0;
	while (ft_isdigit(*str))
	{
		digit = *str - '0';
		i = (10 * i) + digit;
		str++;
	}
	return (i * sign);
}
