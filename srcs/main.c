/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:16:18 by brhajji-          #+#    #+#             */
/*   Updated: 2022/03/02 16:38:56 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/pipex.h"


void init_input(char **av, t_input **input, char **envp)
{
	char	**tmp;

	*input = malloc(sizeof(t_input));
	if (!input)
		return ;
	(*input)->path = get_path(envp);
	tmp = ft_split(av[2], ' ');
	(*input)->cmd[0].cmd = ft_strjoin("/", tmp[0]);
	(*input)->cmd[0].arg = tmp + 1;
	tmp = ft_split(av[3], ' ');
	(*input)->cmd[1].cmd = ft_strjoin("/", tmp[0]);
	(*input)->cmd[1].arg = tmp + 1;
}

void	pipex(t_input **input)
{
	if (pipe(input->fd) == -1)
		return 1;//TODO
	input->child1 = fork();
    if (input->child1 < 0)
         return (perror("Fork: ")); //TODO
}

int	main(int ac, char **av, char **envp)
{
	t_input *input;

	input = NULL;
	if (ac == 5)
	{
		init_input(av, &input, envp);
		ft_printf("%i\n", check_cmd(input, 0));
		if (!input)
			return (1); //TODO
		if (!print_err(check_parsing(av)))
			return (0);


	}
	
	return (0);
}