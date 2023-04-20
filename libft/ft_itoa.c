/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khoubaib <khoubaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 20:43:23 by khoubaib          #+#    #+#             */
/*   Updated: 2022/10/07 20:44:56 by khoubaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_getlen(long nb)
{
	int	count;

	count = 0;
	if (nb < 0)
	{
		count++;
		nb = -nb;
	}
	while (nb >= 1)
	{
		count++;
		nb = nb / 10;
	}
	return (count);
}

static char	*ft_core_itoa(char *ptr, long nb, int len, short sign)
{
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	ptr[len] = '\0';
	while (--len > 0)
	{
		ptr[len] = (nb % 10) + '0';
		nb = nb / 10;
	}
	if (sign)
		ptr[0] = '-';
	else
		ptr[0] = (nb % 10) + '0';
	return (ptr);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	long	nb;
	int		len;
	short	sign;

	sign = 0;
	nb = n;
	ptr = (void *)0;
	len = ft_getlen(nb);
	if (n < 0)
	{
		nb *= -1;
		sign = 1;
	}
	if (nb == 0)
		return (ft_strdup("0"));
	ptr = ft_core_itoa(ptr, nb, len, sign);
	if (!ptr)
		return (NULL);
	return (ptr);
}
