/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 13:33:04 by rkoop             #+#    #+#             */
/*   Updated: 2022/08/04 16:22:39 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_release(char *tmp, char *line)
{
	free(tmp);
	free(line);
	return (NULL);
}

ssize_t	ft_strlen_gnl(const char *str)
{
	ssize_t	len;

	if (str == NULL)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

ssize_t	ft_strlen_nl(char *str)
{
	ssize_t	len;

	if (str == NULL)
		return (0);
	len = 0;
	while (str[len] && str[len] != '\n')
		len++;
	if (str[len] == '\n')
		len++;
	return (len);
}

int	check_nl(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	if (s[i] == '\n')
		return (1);
	return (0);
}

void	ft_strncpy(char *dst, char *src, ssize_t dstsize)
{
	ssize_t	i;

	if (src == NULL)
		src = "\0";
	i = 0;
	while (src[i] && i < dstsize)
	{
		dst[i] = src[i];
		i++;
	}	
	dst[i] = '\0';
}
