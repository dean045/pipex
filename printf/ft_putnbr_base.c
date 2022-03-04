/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 17:50:09 by brhajji-          #+#    #+#             */
/*   Updated: 2022/03/04 15:02:22 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/ft_printf.h"

int	ft_strlen2(char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	print_nbr(unsigned long nbr, char *base, unsigned long taille, int *i)
{
	if (nbr >= taille)
	{
		print_nbr(nbr / taille, base, taille, i);
		print_nbr(nbr % taille, base, taille, i);
	}
	else
	{
		ft_putchar(base[nbr]);
		(*i)++;
	}
}

void	ft_putnbr_base(long nbr, char *base, int *i)
{
	if (nbr < 0)
	{
		write(1, "-", 1);
		(*i)++;
		print_nbr((-nbr), base, ft_strlen2(base), i);
	}
	else
		print_nbr(nbr, base, ft_strlen2(base), i);
}
