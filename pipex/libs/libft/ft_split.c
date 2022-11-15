/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:58:07 by gjupy             #+#    #+#             */
/*   Updated: 2022/08/11 13:05:39 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	count_words(const char *s, char c)
{
	int	words;
	int	i;
	int	len;

	i = -1;
	words = 0;
	len = ft_strlen(s);
	while (++i < len)
	{
		if (s[i] != c)
		{
			while (s[i] != '\0' && s[i] != c)
				i++;
			if (s[i] == c || s[i] == '\0')
				words++;
		}
	}
	return (words);
}

static int	ft_free(char ***ss, size_t j)
{
	if (((*ss)[j]) == NULL)
	{
		while (j-- >= 0)
			free((*ss)[j]);
		free(*ss);
		return (0);
	}
	return (1);
}

static char	**ft_gen(const char *s, char **ss, char c)
{
	int	i;
	int	j;
	int	start;
	int	len;

	i = -1;
	j = 0;
	len = ft_strlen(s);
	while (++i < len)
	{
		start = i;
		if (s[i] != c)
		{
			while (s[i] != '\0' && s[i] != c)
				i++;
			if (s[i] == c || s[i] == '\0')
			{
				ss[j++] = ft_substr(s, start, i - start);
				if (!ft_free(&ss, j - 1))
					return (NULL);
			}
		}
	}
	ss[j] = NULL;
	return (ss);
}

static char	**nulloc(char **ss)
{
	ss = malloc(sizeof(char *));
	ss[0] = NULL;
	return (ss);
}

char	**ft_split(char const *str, char c)
{
	char	**ss;

	if (str == NULL)
		return (NULL);
	ss = NULL;
	if (*str == '\0')
		return (nulloc(ss));
	ss = malloc(sizeof(char *) * (count_words(str, c) + 1));
	if (!ss)
		return (NULL);
	ss = ft_gen(str, ss, c);
	return (ss);
}

// static int	ft_count_words(char const *s, char c)
// {
// 	int	total;
// 	int	i;
// 	int	len;

// 	total = 0;
// 	i = 0;
// 	len = ft_strlen(s);
// 	while (s[i])
// 	{
// 		if (s[i] == c && s[i + 1] != c && i + 1 != len)
// 			total++;
// 		i++;
// 	}
// 	if (total > 1 && s[len - 1] != c)
// 		total++;
// 	if (!total)
// 		total = 1;
// 	return (total);
// }

// static int	ft_free(char ***ss, size_t j)
// {
// 	if (((*ss)[j]) == NULL)
// 	{
// 		while (j-- >= 0)
// 			free((*ss)[j]);
// 		free(*ss);
// 		return (0);
// 	}
// 	return (1);
// }

// static char	**ft_splitting(char **ss, char const *s, char c)
// {
// 	size_t	i;
// 	size_t	j;
// 	size_t	len;

// 	i = 0;
// 	j = 0;
// 	while (s[i])
// 	{
// 		len = 0;
// 		while (s[i] && s[i] != c)
// 		{
// 			i++;
// 			len++;
// 		}
// 		if ((s[i] == c && i) || (!s[i] && (s[ft_strlen(s) - 1] != c)))
// 		{
// 			ss[j++] = ft_substr(s, i - len, len);
// 			if (!ft_free(&ss, j - 1))
// 				return (NULL);
// 		}
// 		while (s[i] && s[i] == c)
// 			i++;
// 	}
// 	ss[j] = NULL;
// 	return (ss);
// }

// static char	**nulloc(char **ss)
// {
// 	ss = malloc(sizeof(char *));
// 	ss[0] = NULL;
// 	return (ss);
// }

// char	**ft_split(char const *s, char c)
// {
// 	char	**ss;

// 	if (s == NULL)
// 		return (NULL);
// 	ss = NULL;
// 	if (*s == '\0')
// 		return (nulloc(ss));
// 	ss = ft_calloc(sizeof(char *) * (ft_count_words(s, c) + 1), 1);
// 	if (ss == NULL)
// 		return (NULL);
// 	ss = ft_splitting(ss, s, c);
// 	return (ss);
// }
