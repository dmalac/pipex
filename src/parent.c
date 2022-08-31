/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parent.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/24 17:11:45 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/08/31 10:24:52 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include "main.h"
#include "libft.h"

char	**get_paths(char **environ)
{
	char	**paths;
	char	*temp;
	size_t	i;

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
				if (!paths[i])
					return (free_array(paths), NULL);
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
		error_and_exit(INIT_ERROR, NULL, NULL);
	tools->cmd = 1;
	tools->total_cmds = argc - 3;
	tools->input_fd = -1;
	tools->output_fd = -1;
	tools->cmd_args = NULL;
	tools->paths = get_paths(envp);
	return (tools);
}

void	pipe_and_fork(int *id, t_tools *tools, int (*pipe_end)[2])
{
	int	pipe_no;

	pipe_no = (tools->cmd % 2 == 0);
	if (tools->cmd < tools->total_cmds)
	{
		if (pipe(pipe_end[pipe_no]) < 0)
			error_and_exit(errno, tools, NULL);
	}
	*id = fork();
	if (*id < 0)
		error_and_exit(errno, tools, NULL);
}

void	close_unnecessary_pipes(t_tools *tools, int pipe_end[2][2])
{
	int	reading_pipe;
	int	writing_pipe;

	reading_pipe = ((tools->cmd - 1) % 2 == 0);
	writing_pipe = (tools->cmd % 2 == 0);
	if (tools->cmd < tools->total_cmds)
		close(pipe_end[writing_pipe][W]);
	if (tools->cmd > 1)
		close(pipe_end[reading_pipe][R]);
}

int	wait_for_last_child(int id, size_t total_cmds)
{
	int	wait_status;
	int	exit_code;

	waitpid(id, &wait_status, 0);
	if (WIFEXITED(wait_status))
		exit_code = WEXITSTATUS(wait_status);
	else
		exit_code = 1;
	while (total_cmds > 1)
	{
		wait(&wait_status);
		total_cmds--;
	}
	return (exit_code);
}
