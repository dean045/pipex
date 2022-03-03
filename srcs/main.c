/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:16:18 by brhajji-          #+#    #+#             */
/*   Updated: 2022/03/02 20:34:22 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/pipex.h"

int clean_pipex(t_input *input)
{
	if (input)
	{
		if (input->path)
			free(input->path);
		if (input->cmd[0].cmd)
			free(input->cmd[0].cmd);
		if (input->cmd[1].cmd)
			free(input->cmd[1].cmd);
		if (input->cmd[0].arg)
			free(input->cmd[0].arg);
		if (input->cmd[1].arg)
			free(input->cmd[1].arg);
		free(input);
		input = NULL;
	}
	return (0);
}

void init_input(char **av, t_input **input, char **envp)
{
	char	**tmp;

	*input = malloc(sizeof(t_input));
	if (!input)
		return ;
	(*input)->path = get_path(envp);
	tmp = ft_split(av[2], ' ');
	(*input)->cmd[0].cmd = ft_strjoin("/", tmp[0]);
	(*input)->cmd[0].arg = tmp;
	tmp = ft_split(av[3], ' ');
	(*input)->cmd[1].cmd = ft_strjoin("/", tmp[0]);
	(*input)->cmd[1].arg = tmp;
	(*input)->f1 = open(av[1], O_RDONLY);
    (*input)->f2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
}

int	main(int ac, char **av, char **envp)
{
	t_input *input;

	input = NULL;
	if (ac == 5)
	{
		init_input(av, &input, envp);
		if (input->f1 < 0 || input->f2 < 0)
			return (clean_pipex(input) && print_err(-1));
		if (!input)
			return (clean_pipex(input) && print_err(99));
		if (!print_err(check_parsing(av)))
			return (clean_pipex(input));
		pipex(input, envp);
		return (clean_pipex(input));
	}
	else
		return (print_err(50));
	return (1);
}