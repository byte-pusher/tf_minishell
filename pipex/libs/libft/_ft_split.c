/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _ft_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:31:30 by bogunlan          #+#    #+#             */
/*   Updated: 2022/06/24 21:36:42 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define TRUE 1
#define FALSE 0

static int	ft_word_count(char const *s, char c)
{
	int				in_word;
	int				word_count;
	unsigned int	i;

	i = 0;
	word_count = 0;
	while ((int)i < ft_strlen(s))
	{
		if (s[i] != c)
		{
			in_word = TRUE;
			while ((in_word) && (++i))
			{
				if ((s[i] == c) || s[i] == '\0')
				{
					word_count++;
					in_word = FALSE;
				}
			}
		}
		i++;
	}
	return (word_count);
}

char	**ft_gen(const char *s, char c, char **res, int res_st_i)
{
	unsigned int	i;
	int				in_word;
	int				word_start;

	i = 0;
	while ((int)i < ft_strlen(s))
	{
		word_start = i;
		if (s[i] != c)
		{
			in_word = TRUE;
			while ((in_word) && (++i))
			{
				if ((s[i] == c) || (s[i] == '\0'))
				{
					res[res_st_i++] = ft_substr(s, word_start, i - word_start);
					in_word = FALSE;
				}
			}
		}
		i++;
	}
	res[res_st_i] = NULL;
	return (res);
}

char	**ft_splito(char const *s, char c)
{
	char	**sarray;
	int		sarray_start_index;

	sarray_start_index = 0;
	if (s == NULL)
		return (NULL);
	sarray = (char **) malloc(sizeof(char *) * (ft_word_count(s, c) + 1));
	if (!sarray)
		return (NULL);
	sarray = ft_gen(s, c, sarray, sarray_start_index);
	return (sarray);
}
