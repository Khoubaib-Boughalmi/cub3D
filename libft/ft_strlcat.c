/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal <kboughal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 21:11:48 by khoubaib          #+#    #+#             */
/*   Updated: 2022/10/10 15:13:06 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	dlen;
	unsigned int	slen;

	i = 0;
	j = 0;
	slen = ft_strlen(src);
	if (!size)
		return (slen);
	j = ft_strlen(dest);
	dlen = j;
	if (size <= dlen)
		return (slen + size);
	while (src[i] != '\0' && size - dlen - 1 > i)
	{
		dest[j] = src[i];
		i++;
		j++;
	}
		dest[j] = '\0';
	return (dlen + slen);
}
