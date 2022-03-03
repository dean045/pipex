/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:27:20 by brhajji-          #+#    #+#             */
/*   Updated: 2022/03/01 14:54:57 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/pipex.h"

int	print_err(int	code)
{
	if (code)
	{
		if (code >= 1 && code <= 4)
			perror("Bad input.\n");
		if (code == 99)
			perror("Error.\n");
		if (code == -1)
			perror("Can't open the file.\n");
		if (code == 50)
			perror("Invalid args.\n");
		return (1);
	}
	return (0);
}