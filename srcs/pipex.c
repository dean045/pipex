/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:40:10 by brhajji-          #+#    #+#             */
/*   Updated: 2022/03/03 16:55:56 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/pipex.h"

void run(t_input *input, int cmd, char **envp)
{
	if(check_cmd(input, cmd))
	{
		if (cmd == 0)
		{
			dup2(input->f1, STDIN_FILENO);
			dup2(input->fd[1], STDOUT_FILENO);
			close(input->fd[0]); 
		}
		else if (cmd == 1)
		{
			input->f2 = open(input->tmp, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (input->f2 == -1)
			{
				perror("Outfile ");
				exit(1);
			}
			dup2(input->f2, STDOUT_FILENO);
			dup2(input->fd[0], STDIN_FILENO);
			close(input->fd[1]);
		}
		if (execve(input->cmd[cmd].cmd, input->cmd[cmd].arg, envp) == -1)
		{
			perror("Execve ");//todo;
			exit(1);
		}
	}
}

void	pipex(t_input *input, char **envp)
{
	int status;
	
	if (pipe(input->fd) < 0)
		return ;//TODO
	input->child1 = fork();
    if (input->child1 < 0)
         return (perror("Fork ")); //TODO
    if (input->child1 == 0)
	{
        run(input, 0, envp);
	}
    input->child2 = fork();
    if (input->child2 < 0)
         return (perror("Fork: "));
    if (input->child2 == 0)
        run(input, 1, envp);
    close(input->fd[0]);         // this is the parent
    close(input->fd[1]);         // doing nothing
    waitpid(input->child1, &status, 0);  // supervising the children
    waitpid(input->child2, &status, 0);  // while they finish their tasks
	//wait(NULL);
}
