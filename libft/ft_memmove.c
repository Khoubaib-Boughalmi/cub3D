/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khoubaib <khoubaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 20:58:11 by khoubaib          #+#    #+#             */
/*   Updated: 2022/10/07 20:58:54 by khoubaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *s1, const void *s2, size_t n)
{
	const char	*p2;
	char		*p1;

	p1 = s1;
	p2 = s2;
	if (p1 == p2)
		return (p1);
	if ((p2 < p1) && (p1 < p2 + n))
	{
		p1 = p1 + n;
		p2 = p2 + n;
		while (n-- != 0)
			*--p1 = *--p2;
	}
	else
	{
		while (n-- != 0)
			*p1++ = *p2++;
	}
	return (s1);
}
