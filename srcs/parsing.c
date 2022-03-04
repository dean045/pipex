/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:29:58 by brhajji-          #+#    #+#             */
/*   Updated: 2022/03/04 16:51:30 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/pipex.h"

int	check_parsing(char **str)
{
	int	i;

	i = 0;
	while (++i < 5)
	{
		if (!str[i][0])
			return (i);
	}
	return (0);
}

char	**get_path(char **envp)
{
	int		i;
	char	**path;

	path = NULL;
	i = -1;
	if (!envp)
		return (NULL);
	while (envp[++i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A' && envp[i][2] == 'T'
			&& envp[i][3] == 'H' && envp[i][4] == '=')
		{
			path = ft_split(envp[i] + 5, ':');
			return (path);
		}
	}
	return (path);
}

int	check_cmd(t_input *input, int cmd)
{
	int		i;
	char	*tmp;

	i = -1;
	if (!access(input->cmd[cmd].cmd, F_OK))
		return (1);
	while (input->path[++i])
	{
		tmp = ft_strjoin(input->path[i], input->cmd[cmd].cmd);
		if (!access(tmp, F_OK))
		{
			free(input->cmd[cmd].cmd);
			input->cmd[cmd].cmd = tmp;
			return (1);
		}
		free(tmp);
	}
	return (0);
}

int	check_file(char *file)
{
	int	fd;

	fd = open(file, __O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		return (-2);
	}
	return (access(file, F_OK));
}
