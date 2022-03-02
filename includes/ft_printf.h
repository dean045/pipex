/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 12:30:17 by brhajji-          #+#    #+#             */
/*   Updated: 2022/03/02 12:08:06 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include<stdio.h>
# include<stdlib.h>
# include<unistd.h>
# include <stdarg.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int		ft_printf(const char *format, ...);
void	ft_putstr_fd(char *s, int fd, int *x);
void	ft_putnbr_fd(long n, int fd, int *i);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_base(long nbr, char *base, int *i);
#endif
