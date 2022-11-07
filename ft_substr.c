/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:09:51 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/07 21:21:15 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/shell.h"

int	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	int		i;

	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) < (int)len)
		len = ft_strlen(&s[start]);
	i = 0;
	sub = malloc(len + 1);
	if (sub == NULL)
		return (NULL);
	while (s[start] && len-- && start <= (unsigned int)ft_strlen(s))
		sub[i++] = s[start++];
	sub[i] = '\0';
	return (sub);
}
