/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal <kboughal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 16:56:00 by kboughal          #+#    #+#             */
/*   Updated: 2022/10/29 16:56:00 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	check_dtype(va_list ap, char c, int *count)
{
	if (c == 'c')
		*count += ft_putchar(va_arg(ap, int));
	else if (c == 's')
		*count += ft_putstr(va_arg(ap, char *));
	else if (c == 'd' || c == 'i')
		ft_putnbr(va_arg(ap, int), count);
	else if (c == 'u')
		ft_put_unsigned_nbr(va_arg(ap, unsigned int), count);
	else if (c == '%')
		*count += ft_putchar('%');
	else if (c == 'x' || c == 'X')
		ft_puthex(va_arg(ap, long), count, c);
	else if (c == 'p')
	{
		*count += ft_putstr("0x");
		ft_putaddress(va_arg(ap, long), count);
	}
	return (*count);
}

int	ft_printf(const char *mand, ...)
{
	int			count;
	int			i;
	va_list		ap;

	va_start(ap, mand);
	i = 0;
	count = 0;
	while (mand[i])
	{
		if (mand[i] == '%' && mand[i + 1])
		{
			i++;
			check_dtype(ap, mand[i], &count);
		}
		else
			count += ft_putchar(mand[i]);
		i++;
	}
	return (count);
}
