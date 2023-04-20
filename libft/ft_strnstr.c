/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khoubaib <khoubaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 21:15:08 by khoubaib          #+#    #+#             */
/*   Updated: 2022/10/07 21:15:59 by khoubaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *lit, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	len = ft_strlen(lit);
	if (!len)
		return ((char *)big);
	if (n != 0)
	{
		while (big[i] != '\0' && n >= len && i <= n - len)
		{
			j = 0;
			while (lit[j] != '\0' && lit[j] == big[i + j])
				j++;
			if (lit[j] == '\0')
				return ((char *)(big + i));
			i++;
		}
	}
	return ((void *)0);
}
