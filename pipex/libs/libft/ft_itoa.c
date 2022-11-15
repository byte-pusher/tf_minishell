/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:07:08 by gjupy             #+#    #+#             */
/*   Updated: 2022/05/05 14:37:18 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_digits(int n)
{
	int	count;

	count = 0;
	if (!n)
		count = 1;
	while (n)
	{
		count++;
		n /= 10;
	}
	return (count);
}

static char	*ft_gotta_malloc(int n)
{
	char	*s;

	if (n < 0)
		s = malloc(ft_count_digits(n) + 2);
	else
		s = malloc(ft_count_digits(n) + 1);
	return (s);
}

static int	ft_pos_or_neg(long *p, char *s)
{
	int	i;

	if (*p < 0)
	{
		*s = '-';
		i = ft_count_digits((int)*p);
		*p *= -1;
	}
	else
		i = ft_count_digits((int)*p) - 1;
	return (i);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		i;
	long	n2;

	s = ft_gotta_malloc(n);
	if (s == NULL)
		return (NULL);
	n2 = n;
	i = ft_pos_or_neg(&n2, s);
	s[i + 1] = '\0';
	while (n2)
	{
		s[i] = (n2 % 10) + '0';
		i--;
		n2 /= 10;
	}
	if (n == 0)
		*s = '0';
	return (s);
}
