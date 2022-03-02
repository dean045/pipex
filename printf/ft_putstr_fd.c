/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:08:35 by brhajji-          #+#    #+#             */
/*   Updated: 2021/12/01 16:00:00 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include<unistd.h>

void	ft_putstr_fd(char *s, int fd, int *x)
{
	unsigned int	i;

	i = 0;
	if (s == NULL)
	{
		ft_putstr_fd("(null)", 1, x);
		return ;
	}
	while (s && s[i])
	{
		write(fd, &s[i], 1);
		i++;
		(*x)++;
	}
}
