/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:16:18 by brhajji-          #+#    #+#             */
/*   Updated: 2022/03/04 18:02:46 by brhajji-         ###   ########.fr       */
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
		free(input);
		input = NULL;
	}
	return (x);
}

int	init_cmd(char **av, t_input *input)
{
	char	**tmp;
	int		i;

	input->cmd = malloc(sizeof(t_cmd *) * (input->nb_cmd + 1));
	if (!input->cmd)
		return (-1);
	i = -1;
	while (++i < input->nb_cmd)
	{
		input->cmd[i] = malloc(sizeof(t_cmd));
		tmp = ft_split(av[i + 2], ' ');
		if (!input->cmd || !tmp)
			return (-1);
		input->cmd[i]->cmd = ft_strjoin("/", tmp[0]);
		input->cmd[i]->arg = tmp;
	}
	return (0);
}

int	init_input(char **av, int ac, t_input **input, char **envp)
{

	*input = malloc(sizeof(t_input));
	if (!input)
		return (1);
	(*input)->f1 = 0;
	(*input)->f2 = 0;
	(*input)->nb_cmd = ac - 3;
	(*input)->fd = malloc(sizeof(t_fd) * (ac - 4));
	if (init_cmd(av , *input))
		return (1);
	(*input)->path = get_path(envp);
	if (!check_file(av[1]))
	{
		(*input)->f1 = open(av[1], O_RDONLY);
		return (0);
	}
	else if (check_file(av[1]) == -2)
		ft_printf("Infile : The infile is a directory.\n");
	else
		perror("Infile ");
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_input	*input;

	input = NULL;
	if (ac >= 5 && !check_parsing(av))
	{
		if (init_input(av, ac, &input, envp))
			return (clean_pipex(input, 0) && print_err(-1));
		if (!input)
			return (clean_pipex(input, 0) && print_err(99));
		pipex(input, envp);
		return (clean_pipex(input, 0));
	}
	else
		return (print_err(50));
	return (1);
}
