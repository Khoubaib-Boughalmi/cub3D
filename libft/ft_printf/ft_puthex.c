/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal <kboughal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 17:23:50 by kboughal          #+#    #+#             */
/*   Updated: 2022/10/29 17:23:50 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_puthex(unsigned int n, int *count, char c)
{
	char	*s1;
	char	*s2;
	char	*hex;

	s1 = "0123456789abcdef";
	s2 = "0123456789ABCDEF";
	if (!n)
	{
		*count += ft_putchar('0');
		return ;
	}
	if (c == 'x')
		hex = s1;
	else
		hex = s2;
	if (n < 16)
		*count += ft_putchar(hex[n]);
	else
	{
		ft_puthex(n / 16, count, c);
		ft_puthex(n % 16, count, c);
	}
}

void	ft_putaddress(unsigned long int n, int *count)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (!n)
	{
		*count += write(1, "0", 1);
		return ;
	}
	if (n < 16)
		*count += ft_putchar(hex[n]);
	else
	{
		ft_putaddress(n / 16, count);
		ft_putaddress(n % 16, count);
	}
}
