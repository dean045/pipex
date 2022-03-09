/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:40:10 by brhajji-          #+#    #+#             */
/*   Updated: 2022/03/09 16:50:58 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/pipex.h"

void	close_pipe(t_input *input)
{
	int	i;

	i = -1;
	while (++i < input->nb_cmd -1)
	{
		close(input->fd[i].fd[0]);
		close(input->fd[i].fd[1]);
	}
}

void	first_cmd(t_input *input, int cmd, char **envp)
{
	pid_t	pid;

	if (check_cmd(input, cmd))
	{
		pid = fork();
		if (pid < 0)
			return (perror("Fork "));
		if (pid == 0 && check_cmd(input, cmd))
		{
			dup2(input->f1, STDIN_FILENO);
			dup2(input->fd[cmd].fd[1], STDOUT_FILENO);
			close(input->fd[cmd].fd[0]);
			close(input->f1);
			if (execve(input->cmd[cmd]->cmd, input->cmd[cmd]->arg, envp) == -1)
			{
				perror("Execve ");
				exit(clean_pipex(input, 1));
			}
			close_pipe(input);
			clean_pipex(input, 0);
		}
	}
	else
		perror("Command ");
}

void	last_cmd(t_input *input, int cmd, char **envp)
{
	pid_t	pid;

	if (!check_cmd(input, cmd))
		return (perror("Command "));
	pid = fork();
	if (pid < 0)
		return (perror("Fork "));
	if (pid == 0)
	{
		if (check_f2(input))
			exit(clean_pipex(input, 1));
		dup2(input->f2, STDOUT_FILENO);
		dup2(input->fd[cmd - 1].fd[0], STDIN_FILENO);
		close(input->fd[cmd - 1].fd[1]);
		close(input->f2);
		if (execve(input->cmd[cmd]->cmd, input->cmd[cmd]->arg, envp) == -1)
		{
			perror("Execve ");
			exit(clean_pipex(input, 1));
		}
		close_pipe(input);
		clean_pipex(input, 0);
	}
}

void	run(t_input *input, int cmd, char **envp)
{
	pid_t	pid;

	if (check_cmd(input, cmd))
	{
		pid = fork();
		if (pid < 0)
			return (perror("Fork "));
		if (pid == 0 && check_cmd(input, cmd))
		{
			dup2(input->fd[cmd - 1].fd[0], STDIN_FILENO);
			dup2(input->fd[cmd].fd[1], STDOUT_FILENO);
			close(input->fd[cmd - 1].fd[1]);
			close(input->fd[cmd].fd[0]);
			if (execve(input->cmd[cmd]->cmd, input->cmd[cmd]->arg, envp) == -1)
			{
				perror("Execve ");
				exit(clean_pipex(input, 1));
			}
			close_pipe(input);
			clean_pipex(input, 0);
		}
	}
	else
		perror("Command ");
}
