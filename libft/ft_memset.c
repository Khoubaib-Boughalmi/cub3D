/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khoubaib <khoubaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 20:59:20 by khoubaib          #+#    #+#             */
/*   Updated: 2022/10/07 20:59:41 by khoubaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t len)
{
	size_t	i;
	char	*new_str;

	i = 0;
	new_str = (char *) str;
	while (i < len)
	{
		new_str[i] = c;
		i++;
	}
	return ((void *)(new_str));
}
