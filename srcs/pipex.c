/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:40:10 by brhajji-          #+#    #+#             */
/*   Updated: 2022/03/02 20:33:04 by brhajji-         ###   ########.fr       */
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
			close(input->fd[1]); 
		}
		if (cmd == 1)
		{
			dup2(input->fd[0], STDIN_FILENO);
			close(input->fd[0]);
			dup2(input->f2, STDOUT_FILENO);
		}
		if(execve(input->cmd[cmd].cmd, input->cmd[cmd].arg, envp) == -1)
		{
			perror("Error");//todo;
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
         return (perror("Fork: ")); //TODO
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
}
