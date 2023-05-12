/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechaoub <aechaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:50:14 by aechaoub          #+#    #+#             */
/*   Updated: 2023/05/12 17:51:15 by aechaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_cpy(char *str, char *s, int k)
{
	int	i;

	i = 0;
	while (s[i])
	{
		str[i + k] = s[i];
		i++;
	}
	return (i);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*p;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1)
		s1 = ft_strdup("");
	if (!s2)
	{
		p = ft_strdup(s1);
		free(s1);
		return (p);
	}
	p = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!p)
		return (0);
	i = ft_cpy(p, s1, 0);
	j = ft_cpy(p, s2, i);
	p[i + j] = 0;
	free(s1);
	return (p);
}

int	min(int a, int b)
{
	if (a > b)
		return (b);
	return (a);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char		*p;
	size_t		i;
	size_t		y;

	if (s == NULL)
		return (NULL);
	i = 0;
	y = min(ft_strlen(s), len);
	p = malloc((y + 1) * sizeof(char));
	if (!p)
		return (0);
	while (i < len && start < ft_strlen(s))
	{
		p[i] = s[start];
		i++;
		start++;
	}
	p[i] = 0;
	free(s);
	return (p);
}

char	*ft_strdup(const char *src)
{
	char	*new;
	int		i;
	int		size;

	size = 0;
	while (src[size])
		++size;
	new = malloc(sizeof(char) * (size + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (src[i])
	{
		new[i] = src[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
