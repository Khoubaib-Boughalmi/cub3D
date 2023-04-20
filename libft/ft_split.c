/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal <kboughal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 21:02:32 by khoubaib          #+#    #+#             */
/*   Updated: 2022/10/10 17:04:13 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_word_count(char const *str, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && str[i] == c)
			i++;
		if (str[i] != '\0')
			count++;
		while (str[i] != '\0' && str[i] != c)
			i++;
		while (str[i] != '\0' && str[i] == c)
			i++;
	}
	return (count);
}

static size_t	ft_word_len(char const *str, char c)
{
	size_t	count;

	count = 0;
	while (str[count] != '\0' && str[count] != c)
		count++;
	return (count);
}

static char	*ft_copy(char const *s, char c, int *i)
{
	int		word_len;
	char	*ptr;
	int		j;

	word_len = ft_word_len(&s[*i], c);
	ptr = (char *)malloc(sizeof(char) * (word_len + 1));
	if (!ptr)
		return (NULL);
	j = 0;
	while (j < word_len)
	{
		ptr[j++] = s[*i];
		*i += 1;
	}
	ptr[j] = '\0';
	return (ptr);
}

static char	**ft_free(char **ptr, int k)
{
	while (k--)
		free(ptr[k]);
	free(ptr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		k;
	char	**ptr;

	i = 0;
	k = 0;
	ptr = (char **)malloc((ft_word_count(s, c) + 1) * sizeof(char *));
	if (!ptr)
		return (NULL);
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != '\0')
		{
			ptr[k] = ft_copy(s, c, &i);
			if (!ptr[k])
				return (ft_free(ptr, k));
			k++;
		}
	}
	ptr[k] = 0;
	return (ptr);
}
