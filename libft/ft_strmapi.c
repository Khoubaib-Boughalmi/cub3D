/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khoubaib <khoubaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 21:13:32 by khoubaib          #+#    #+#             */
/*   Updated: 2022/10/07 21:14:21 by khoubaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ptr;
	int		slen;
	int		i;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	i = 0;
	ptr = (char *)malloc(sizeof(char) * (slen + 1));
	if (!ptr)
		return (NULL);
	while (s[i] != '\0')
	{
		ptr[i] = (*f)(i, s[i]);
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
