/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parent.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/24 17:11:45 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/08/24 18:40:49 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "main.h"
#include "libft.h"

char	**get_paths(char **environ)
{
	char		**paths;
	char		*temp;
	size_t		i;

	paths = NULL;
	i = 0;
	while (environ[i] && ft_strncmp(environ[i], "PATH=", 5) != 0)
		i++;
	if (environ[i])
	{
		paths = ft_split(environ[i] + 5, ':');
		if (paths)
		{
			i = -1;
			while (paths[++i])
			{
				temp = paths[i];
				paths[i] = ft_strjoin(paths[i], "/");
				free (temp);
			}
		}
	}
	return (paths);
}

t_tools	*tools_init(int argc, char **envp)
{
	t_tools	*tools;

	tools = malloc(sizeof(t_tools));
	if (!tools)
		error_and_exit(INIT_ERROR);
	tools->cmd = 0;
	tools->total_cmds = argc - 3;
	tools->input_fd = -1;
	tools->output_fd = -1;
	tools->cmd_args = NULL;
	tools->paths = get_paths(envp);
	return (tools);
}

void	pipe_and_fork(int *id, size_t cmd, size_t total_cmds, \
int (*pipe_end)[2])
{
	int	pipe_no;

	pipe_no = (cmd % 2 == 0);
	if (cmd < total_cmds)
	{
		if (pipe(pipe_end[pipe_no]) < 0)
		{
			perror("Pipe error");
			error_and_exit(PIPE_ERROR);
		}
	}
	*id = fork();
	if (*id < 0)
	{
		perror("Fork error");
		error_and_exit(FORK_ERROR);
	}
}

void	close_unnecessary_pipes(size_t cmd, int pipe_end[2][2])
{
	int	reading_pipe;
	int	writing_pipe;

	reading_pipe = ((cmd - 1) % 2 == 0);
	writing_pipe = (cmd % 2 == 0);
	close(pipe_end[writing_pipe][W]);
	if (cmd > 1)
		close(pipe_end[reading_pipe][R]);
}
