/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   child.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 18:49:30 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/08/29 14:40:27 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "libft.h"
#include <unistd.h>

static char	*prepare_cmd(char *cmd, char **paths)
{
	int		i;
	char	*full_cmd;

	if (access(cmd, F_OK) == 0)
		return (cmd);
	i = 0;
	while (paths && paths[i])
	{
		full_cmd = ft_strjoin(paths[i++], cmd);
		if (access(full_cmd, F_OK) == 0)
		{
			free(cmd);
			return (full_cmd);
		}
		else
			free (full_cmd);
	}
	return (cmd);
}

static void	get_tools(t_tools *tools, char **argv, int pipe_end[2][2])
{
	if (tools->cmd == 1)
		tools->input_fd = get_infile_fd(argv[1]);
	else
		tools->input_fd = pipe_end[tools->cmd % 2 == 1][R];
	if (tools->cmd == tools->total_cmds)
		tools->output_fd = get_outfile_fd(argv[tools->total_cmds + 2]);
	else
		tools->output_fd = pipe_end[tools->cmd % 2 == 0][W];
	tools->cmd_args = ft_split(argv[tools->cmd + 1], ' ');
	if (!tools->cmd_args)
		error_and_exit(PARSING_ERROR, tools, NULL);
	tools->cmd_args[0] = prepare_cmd(tools->cmd_args[0], tools->paths);
}

static void	close_pipes_child(size_t cmd, size_t total_cmds, \
int pipe_end[2][2], int when)
{
	if (when == BEFORE)
	{
		if (cmd < total_cmds)
			close(pipe_end[cmd % 2 == 0][R]);
	}
	if (when == AFTER)
	{
		close(pipe_end[cmd % 2 == 0][W]);
		if (cmd > 1)
			close(pipe_end[(cmd - 1) % 2 == 0][R]);
	}
}

void	perform_cmd(t_tools *tools, char **argv, int pipe_end[2][2], \
char **envp)
{
	int	result;

	result = 0;
	get_tools(tools, argv, pipe_end);
	close_pipes_child(tools->cmd, tools->total_cmds, pipe_end, BEFORE);
	dup2(tools->input_fd, STDIN_FILENO);
	dup2(tools->output_fd, STDOUT_FILENO);
	if (tools->input_fd >= 0 && tools->output_fd >= 0)
		result = execve(tools->cmd_args[0], tools->cmd_args, envp);
	close_pipes_child(tools->cmd, tools->total_cmds, pipe_end, AFTER);
	if (result < 0)
		error_and_exit(CMD_ERROR, tools, tools->cmd_args[0]);
}
