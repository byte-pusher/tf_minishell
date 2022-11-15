/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_dup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 15:24:48 by gjupy             #+#    #+#             */
/*   Updated: 2022/06/24 22:56:31 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strchr_dup(char **s1, char *s2)
{
	int	i;
	int	len_s1;
	int	len_s2;

	len_s2 = ft_strlen(s2);
	i = -1;
	while (s1[++i])
	{
		len_s1 = ft_strlen(s1[i]);
		if ((len_s1 == len_s2) && ft_strncmp(s1[i], s2, len_s1) == 0)
			return (i);
	}
	return (-1);
}
