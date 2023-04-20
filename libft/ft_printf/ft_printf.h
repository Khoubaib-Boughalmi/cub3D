/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal <kboughal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 17:01:29 by kboughal          #+#    #+#             */
/*   Updated: 2022/10/29 17:01:29 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *mand, ...);
int		check_dtype(va_list ap, char c, int *count);
int		ft_putchar(char c);
int		ft_putstr(char *str);

void	ft_putnbr(int n, int *count);
void	ft_puthex(unsigned int n, int *count, char c);
void	ft_putaddress(unsigned long int n, int *count);
void	ft_put_unsigned_nbr(unsigned int n, int *count);
#endif