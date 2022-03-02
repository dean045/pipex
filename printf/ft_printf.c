/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 11:58:23 by brhajji-          #+#    #+#             */
/*   Updated: 2022/03/02 12:11:17 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/ft_printf.h"

void	len_and_print(char c, va_list ap, int *x)
{
	if (c == 's')
		ft_putstr_fd(va_arg(ap, char *), 1, x);
	else if (c == 'i')
		ft_putnbr_fd(va_arg(ap, int), 1, x);
	else if (c == 'd')
		ft_putnbr_fd(va_arg(ap, int), 1, x);
	else if (c == 'u')
		ft_putnbr_fd(va_arg(ap, unsigned int), 1, x);
	else if (c == 'X')
		ft_putnbr_base(va_arg(ap, unsigned int), "0123456789ABCDEF", x);
	else if (c == 'x')
		ft_putnbr_base(va_arg(ap, unsigned int), "0123456789abcdef", x);
	else if (c == 'p')
	{
		ft_putstr_fd("0x", 1, x);
		ft_putnbr_base(va_arg(ap, unsigned long), "0123456789abcdef", x);
	}
}

int	checkf(char c, va_list ap, int *x)
{
	if (c != 's' && c != '%' && c != 'i' && c != 'u' && c != 'X'
		&& c != 'c' && c != 'x' && c != 'd' && c != 'p')
	{
		(*x)++;
		return (1);
	}
	else if (c == '%')
	{
		ft_putchar_fd('%', 1);
		(*x)++;
	}
	else if (c == 'c')
	{
		ft_putchar_fd(va_arg(ap, int), 1);
		(*x)++;
	}
	else
		len_and_print(c, ap, x);
	return (2);
}

int	ft_printf(const char *format, ...)
{
	char	*temp;
	size_t	i;
	int		x;
	va_list	ap;

	va_start(ap, format);
	temp = (char *)format;
	i = 0;
	x = 0;
	while (temp[i])
	{
		if (temp[i] == '%' && temp[i + 1])
			i += checkf(temp[i + 1], ap, &x);
		else
		{
			ft_putchar_fd(temp[i], 1);
			i++;
			x++;
		}
	}
	return (x);
}
