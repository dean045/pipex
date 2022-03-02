/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:26:40 by brhajji-          #+#    #+#             */
/*   Updated: 2022/03/02 12:11:20 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>
#include"../includes/ft_printf.h"

void	ft_putnbr_fd(long n, int fd, int *i)
{
	unsigned long	x;
	char			c;

	x = n;
	if (n < 0)
	{
		write(fd, "-", 1);
		x = -n;
		(*i)++;
	}
	if (x < 10)
	{
		c = x + 48;
		write(fd, &c, 1);
		(*i)++;
	}
	else if (x >= 10)
	{
		ft_putnbr_fd(x / 10, fd, i);
		ft_putnbr_fd(x % 10, fd, i);
	}
}
