/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 10:56:48 by brhajji-          #+#    #+#             */
/*   Updated: 2022/03/09 16:47:47 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/pipex.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	clean_pipex(t_input *input, int x)
{
	if (input)
	{
		if (input->path)
			free_tab(input->path);
		if (input->cmd)
			free_cmd(input);
		if (input->f1)
			close(input->f1);
		if (input->f2)
			close(input->f2);
		if (input->fd)
			free(input->fd);
		if (open(".here_doc_tmp", O_RDWR) != -1)
			unlink(".here_doc_tmp");
		free(input);
		input = NULL;
	}
	return (x);
}
