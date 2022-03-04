/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:40:10 by brhajji-          #+#    #+#             */
/*   Updated: 2022/03/04 18:05:04 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/pipex.h"

int	check_f2(t_input *input)
{
	input->f2 = open(input->tmp, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (input->f2 == -1)
	{
		perror("Outfile ");
		return (1);
	}
	return (0);
}

void	run(t_input *input, int cmd, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (perror("Fork "));
	if (pid == 0 && check_cmd(input, cmd))
	{
		if (cmd < input->nb_cmd - 1)
		{
			dup2(input->f1, STDIN_FILENO);
			dup2(input->fd[cmd].fd[1], STDOUT_FILENO);
			close(input->fd[cmd].fd[0]);
		}
		else if (cmd == input->nb_cmd - 1)
		{
			if (check_f2(input))
				exit(clean_pipex(input, 1));
			dup2(input->f2, STDOUT_FILENO);
			dup2(input->fd[cmd -1].fd[0], STDIN_FILENO);
			close(input->fd[cmd -1].fd[1]);
		}
		if (execve(input->cmd[cmd]->cmd, input->cmd[cmd]->arg, envp) == -1)
		{
			perror("Execve ");
			exit(clean_pipex(input, 1));
		}
	}
	else if (!check_cmd(input, cmd))
		perror("Command ");
}

void	pipex(t_input *input, char **envp)
{
	int	status;
	int	i;

	i = -1;
	while (++i < input->nb_cmd)
	{
		if (i < input->nb_cmd -1)
		{
			if (pipe(input->fd[i].fd) < 0)
				return (perror("Pipe "));
			run(input, i, envp);
		}
		close(input->fd[i].fd[0]);
		close(input->fd[i].fd[1]);
	}
	while (--i > 0)
		wait(&status);
}
