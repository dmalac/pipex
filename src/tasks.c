/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tasks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 18:49:30 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/08/22 17:46:10 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "libft.h"
#include <unistd.h>	//for fork()
#include <stdio.h>	// delete

/* CHILD
	if fd infile >= 0
		prepare cmd (find it in paths (if paths), if found, complete the name)
		perform cmd
		write output to the correct fd
	close output fd
	
	function close_unused_pipe_ends(task_no, fds)
		close pipe[w] (if task_no > 1)
		close pipe read (if pipe, i.e. task_no < next->task_no)

		task_no		unused pipe ends
		1 							pipe[0] read
		2			pipe[0] write	pipe[1] read
		3			pipe[1] write	pipe[0] read
		4			pipe[0] write	pipe[1]read
		...
		last		pipe[x] write
		*/

static void	close_unused_pipe_ends(int task_no, t_fds fds)
{
	close(fds.pipe_end[(task_no % 2 == 0)][0]);
	close(fds.pipe_end[(task_no % 2 == 1)][1]);
	printf("\n\t[close unused task %d] I just closed pipe[%d][0] (fd %d) and pipe[%d][1] (fd %d)\n", \
	task_no, (task_no % 2 == 0), fds.pipe_end[(task_no % 2 == 0)][0], (task_no % 2 == 1), fds.pipe_end[(task_no % 2 == 1)][1]);
	if (task_no == 1)
	{
		close(fds.pipe_end[1][0]);
		printf("\t... and also pipe[1][0] (fd %d)\n", fds.pipe_end[1][0]);
	}
}

char	*prepare_cmd(char *cmd, char **paths)
{
	int		i;
	char	*full_cmd;

	if (access(cmd, F_OK) == 0)
		return (cmd);
	i = 0;
	while (paths[i])
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

void	perform_task(t_tasks *task, char **paths, char **envp, t_fds fds)
{
	int	result;

	printf("[child %d] I just started\n", task->task_no);
	close_unused_pipe_ends(task->task_no, fds);
	if (task->input_fd >= 0)
	{
		task->cmd_args[0] = prepare_cmd(task->cmd_args[0], paths);
		printf("[child %d] am about to execve with input fd %d and output fd %d\n", task->task_no, task->input_fd, task->output_fd);
		dup2(task->input_fd, STDIN_FILENO);
		dup2(task->output_fd, STDOUT_FILENO);
		result = execve(task->cmd_args[0], task->cmd_args, envp);
		if (result < 0)
			perror("Execve");
	}
}
