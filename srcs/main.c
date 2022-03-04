/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:16:18 by brhajji-          #+#    #+#             */
/*   Updated: 2022/03/04 14:54:50 by brhajji-         ###   ########.fr       */
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

int	clean_pipex(t_input *input)
{
	if (input)
	{
		if (input->path)
			free_tab(input->path);
		if (input->cmd[0].cmd)
			free(input->cmd[0].cmd);
		if (input->cmd[1].cmd)
			free(input->cmd[1].cmd);
		if (input->cmd[0].arg)
			free_tab(input->cmd[0].arg);
		if (input->cmd[1].arg)
			free_tab(input->cmd[1].arg);
		free(input);
		input = NULL;
	}
	return (0);
}

void	init_input(char **av, t_input **input, char **envp)
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
	if (!check_file(av[1]))
		(*input)->f1 = open(av[1], O_RDONLY);
	else if (check_file(av[1]) == -2)
		ft_printf("Infile : The infile is a directory.\n");
	else
		perror("Infile ");
	(*input)->tmp = av[4];
}

int	main(int ac, char **av, char **envp)
{
	t_input	*input;

	input = NULL;
	if (ac == 5 && !check_parsing(av))
	{
		init_input(av, &input, envp);
		if (input->f1 < 0 || input->f2 < 0)
			return (clean_pipex(input) && print_err(-1));
		if (!input)
			return (clean_pipex(input) && print_err(99));
		pipex(input, envp);
		return (clean_pipex(input));
	}
	else
		return (print_err(50));
	return (1);
}
