/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal <kboughal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 17:15:03 by kboughal          #+#    #+#             */
/*   Updated: 2022/10/29 17:15:03 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr(int n, int *count)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		*count += ft_putchar('-');
		nb = -nb;
	}
	if (nb < 10)
		*count += ft_putchar(nb + '0');
	else
	{
		ft_putnbr(nb / 10, count);
		ft_putnbr(nb % 10, count);
	}
}

void	ft_put_unsigned_nbr(unsigned int n, int *count)
{
	if (n < 10)
		*count += ft_putchar(n + '0');
	else
	{
		ft_putnbr(n / 10, count);
		ft_putnbr(n % 10, count);
	}
}
