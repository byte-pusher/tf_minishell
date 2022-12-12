/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:55:59 by rkoop             #+#    #+#             */
/*   Updated: 2022/12/09 14:06:53 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	c;
	unsigned int	src_len;
	char			*rtr_str;

	c = 0;
	if (s == NULL)
		return (NULL);
	src_len = ft_strlen(s);
	rtr_str = NULL;
	if (start < src_len && len > src_len)
		len = src_len;
	else if (src_len <= start)
		len = 0;
	rtr_str = malloc((len + 1) * sizeof(char));
	if (rtr_str == NULL)
		return (NULL);
	while (c < len && s[start + c] != '\0')
	{
		rtr_str[c] = s[start + c];
		c++;
	}
	rtr_str[c] = '\0';
	return (rtr_str);
}
