/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 12:18:22 by rkoop             #+#    #+#             */
/*   Updated: 2022/12/06 18:18:35 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	count_substrs(char const *s, char c)
{
	int	e;
	int	count;
	int	detect_c;

	e = 0;
	count = 0;
	detect_c = 0;
	while (s[e] != '\0')
	{
		if ((s[e] != c) && detect_c == 0)
		{
			detect_c = 1;
			count++;
		}
		else if (s[e] == c)
			detect_c = 0;
		e++;
	}
	return (count);
}

static size_t	count_substr_len(const char *s, char c, size_t stat)
{
	size_t	i;

	i = 0;
	while (s[stat] && s[stat] != c)
	{
		i++;
		stat++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	int		itwo;
	size_t	len;
	int		nb_of_strs;
	char	**rtr_arr;

	i = 0;
	itwo = 0;
	if (s == NULL)
		return (NULL);
	nb_of_strs = count_substrs(s, c);
	rtr_arr = (char **)malloc((nb_of_strs + 1) * sizeof(char *));
	if (rtr_arr == NULL)
		return (NULL);
	while (i < ft_strlen(s) && itwo < (nb_of_strs))
	{
		while ((s[i] == c))
			i++;
		len = count_substr_len(s, c, i);
		rtr_arr[itwo] = ft_substr(s, i, len);
		itwo++;
		i += len;
	}
	rtr_arr[itwo] = NULL;
	return (rtr_arr);
}
