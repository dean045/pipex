/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:33:45 by brhajji-          #+#    #+#             */
/*   Updated: 2022/03/04 15:19:38 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include<stdlib.h>
# include<unistd.h>
# include <errno.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/wait.h>
# include"../includes/ft_printf.h"

typedef struct s__cmd
{
	char	*cmd;
	char	**arg;
}	t_cmd;

typedef struct s_input
{
	t_cmd	cmd[2];	
	char	**path;
	int		fd[2];
	int		f1;
	int		f2;
	char	*tmp;
	pid_t	child1;
	pid_t	child2;
}	t_input;

int					check_parsing(char **str);
int					print_err(int code);
int					check_file(char *file);
char				**get_path(char **envp);
char				**ft_split(char const *str, char c);
int					check_cmd(t_input *input, int cmd);
long unsigned int	ft_strlen(const char *str);
char				*ft_strjoin(char const *s1, char const *s2);
void				pipex(t_input *input, char **envp);
int					clean_pipex(t_input *input, int x);
#endif