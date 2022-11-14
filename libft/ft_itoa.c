/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 13:31:29 by rkoop             #+#    #+#             */
/*   Updated: 2022/08/13 12:19:25 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	count_digits_ia(int n)
{
	int	count;

	count = 0;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static char	*itoa_negative(int n)
{
	unsigned int		i;
	unsigned int		len;
	char				*rtr_str;

	i = 1;
	len = count_digits_ia(n);
	rtr_str = malloc((sizeof(char) * (len + 2)));
	if (rtr_str == NULL)
		return (NULL);
	if (n == -2147483648)
	{
		ft_strlcpy(rtr_str, "-2147483648", len + 2);
		return (rtr_str);
	}
	rtr_str[0] = '-';
	n = n * -1;
	while (n > 0)
	{
		rtr_str[len] = (n % 10) + '0';
		n = n / 10;
		len--;
		i++;
	}
	rtr_str[i] = '\0';
	return (rtr_str);
}

static char	*itoa_positive(int n)
{
	unsigned int		i;
	unsigned int		len;
	char				*rtr_str;

	i = 0;
	len = count_digits_ia(n);
	rtr_str = malloc((sizeof(char) * (len + 1)));
	if (rtr_str == NULL)
		return (NULL);
	len = len - 1;
	while (n > 0)
	{
		rtr_str[len] = (n % 10) + '0';
		n = n / 10;
		len--;
		i++;
	}
	rtr_str[i] = '\0';
	return (rtr_str);
}

char	*ft_itoa(int n)
{	
	char	*rtr_str;

	if (n == 0)
	{
		rtr_str = malloc((sizeof(char) * (2)));
		if (rtr_str == NULL)
			return (NULL);
		rtr_str[0] = '0';
		rtr_str[1] = '\0';
		return (rtr_str);
	}
	if (n < 0)
	{
		return (itoa_negative(n));
	}
	if (n > 0)
	{
		return (itoa_positive(n));
	}
	return (NULL);
}
