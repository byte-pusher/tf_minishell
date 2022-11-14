/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 20:02:59 by rkoop             #+#    #+#             */
/*   Updated: 2022/04/07 10:17:46 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*con_str;
	int		i;
	int		c;

	i = 0;
	c = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	con_str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (con_str == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		con_str[i] = s1[i];
		i++;
	}
	while (s2[c] != '\0')
	{
		con_str[i] = s2[c];
		i++;
		c++;
	}
	con_str[i] = '\0';
	return (con_str);
}
