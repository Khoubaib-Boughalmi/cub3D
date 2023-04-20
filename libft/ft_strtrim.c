/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khoubaib <khoubaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 21:18:42 by khoubaib          #+#    #+#             */
/*   Updated: 2022/10/07 21:21:36 by khoubaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strtrim_start(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i] != '\0')
	{
		j = 0;
		while (set[j] != '\0')
		{
			if (set[j] == s1[i])
			{
				i++;
				break ;
			}
			j++;
		}
		if (set[j] == '\0')
			break ;
	}
	return (i);
}

static int	ft_strtrim_end(char const *s1, char const *set)
{
	int	len;
	int	j;

	len = ft_strlen(s1) - 1;
	while (len >= 0)
	{
		j = 0;
		while (set[j] != '\0')
		{
			if (set[j] == s1[len])
			{
				len--;
				break ;
			}
			j++;
		}
		if (set[j] == '\0')
			break ;
	}
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		k;
	int		dlen;
	char	*ptr;

	i = ft_strtrim_start(s1, set);
	j = ft_strtrim_end(s1, set);
	dlen = (j - i);
	k = 0;
	if (dlen <= 0)
		return (ft_strdup(""));
	ptr = (char *)malloc(sizeof(char) * (dlen + 2));
	if (!ptr)
		return (NULL);
	while (i <= j)
		ptr[k++] = s1[i++];
	ptr[k] = '\0';
	return (ptr);
}
