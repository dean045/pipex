/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:14:49 by brhajji-          #+#    #+#             */
/*   Updated: 2022/03/09 16:43:23 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/pipex.h"

int	here_doc_init(t_input *input, int size)
{
	int		fd;
	int		ret;
	char	*buff;

	fd = open(".here_doc_tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	ret = 1;
	if (fd == -1)
		return (-1);
	buff = malloc(sizeof(char) * (size + 1));
	if (!buff)
		return (-1);
	while (ret >= 0)
	{
		ret = read(0, buff, size);
		buff[ret] = '\0';
		if (!ft_strcmp(buff, input->limiter))
		{
			free(buff);
			return (fd);
		}
		else
			write(fd, buff, ret);
	}
	free(buff);
	return (fd);
}
