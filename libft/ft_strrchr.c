/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khoubaib <khoubaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 21:16:09 by khoubaib          #+#    #+#             */
/*   Updated: 2022/10/07 21:17:45 by khoubaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	ch;
	int		len;

	len = ft_strlen(s);
	ch = c;
	while (len > -1)
	{
		if (s[len] == ch)
			return (((char *)s) + len);
		len--;
	}
	return (0);
}
