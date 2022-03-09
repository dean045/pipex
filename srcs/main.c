/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:16:18 by brhajji-          #+#    #+#             */
/*   Updated: 2022/03/09 16:51:08 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/pipex.h"

int	init_cmd(char **av, t_input *input, int here_doc)
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
		tmp = ft_split(av[i + 2 + here_doc], ' ');
		if (!input->cmd || !tmp)
			return (-1);
		input->cmd[i]->cmd = ft_strjoin("/", tmp[0]);
		input->cmd[i]->arg = tmp;
	}
	return (0);
}

int	input_suite(char **av, t_input **input, int here_doc)
{
	if (!here_doc)
	{
		if (!check_file(av[1]))
		{
			(*input)->f1 = open(av[1], O_RDONLY);
			return (0);
		}
		else if (check_file(av[1]) == -2)
			ft_printf("Infile : The infile is a directory.\n");
		else
			perror("Infile ");
	}
	else
	{
		(*input)->limiter = av[2];
		if (here_doc_init(*input, ft_strlen((*input)->limiter)) == -1)
			return (1);
		(*input)->f1 = open(".here_doc_tmp", O_RDONLY);
		return (0);
	}
	return (1);
}

int	init_input(char **av, int ac, t_input **input, char **envp)
{
	int	here_doc;

	here_doc = 0;
	if (!ft_strcmp(av[1], "here_doc"))
		here_doc = 1;
	*input = malloc(sizeof(t_input));
	if (!input)
		return (1);
	(*input)->f1 = 0;
	(*input)->f2 = 0;
	(*input)->path = get_path(envp);
	(*input)->tmp = av[ac - 1];
	(*input)->nb_cmd = ac - (3 + here_doc);
	(*input)->fd = malloc(sizeof(t_fd) * (ac - 2 - here_doc));
	if (!(*input)->fd)
		return (1);
	if (init_cmd(av, *input, here_doc))
		return (1);
	return (input_suite(av, input, here_doc));
}

void	pipex(t_input *input, char **envp)
{
	int	status;
	int	i;

	i = -1;
	while (++i < input->nb_cmd)
	{
		if (i < input->nb_cmd - 1)
		{
			if (pipe(input->fd[i].fd) < 0)
				return (perror("Pipe "));
		}
		if (i == 0)
			first_cmd(input, i, envp);
		else if (i == input->nb_cmd -1)
			last_cmd(input, i, envp);
		else
			run(input, i, envp);
		if (i)
			close(input->fd[i - 1].fd[0]);
		if (i < input->nb_cmd - 1)
			close(input->fd[i].fd[1]);
	}
	while (--i > 0)
		wait(&status);
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
