/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:27:20 by brhajji-          #+#    #+#             */
/*   Updated: 2022/03/04 14:55:19 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/pipex.h"

int	print_err(int code)
{
	if (code)
	{
		if (code == 99)
			ft_printf("Error.\n");
		if (code == -1)
			ft_printf("Can't open the file.\n");
		if (code == 50)
			ft_printf("Invalid args.\n");
		return (1);
	}
	return (0);
}
