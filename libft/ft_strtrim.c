/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 17:51:29 by rkoop             #+#    #+#             */
/*   Updated: 2022/04/17 19:40:09 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static unsigned int	check_set(char a, char const *setz)
{
	int	i;

	i = 0;
	while (setz[i])
	{
		if (setz[i] == a)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim_str;
	int		front;
	int		back;
	int		z;

	if (s1 == NULL || set == NULL)
		return (NULL);
	front = 0;
	back = ft_strlen(s1)-1;
	z = 0;
	while (s1[front] != '\0' && check_set(s1[front], set) == 1)
		front++;
	while (back > front && s1[back] != '\0' && check_set(s1[back], set) == 1)
		back--;
	trim_str = (char *)malloc((back - front + 2) * sizeof(char));
	if (trim_str == NULL)
		return (NULL);
	while (front <= back)
		trim_str[z++] = s1[front++];
	trim_str[z] = '\0';
	return (trim_str);
}
