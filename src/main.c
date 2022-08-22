/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/11 16:50:10 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/08/22 16:43:10 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "libft.h"
#include "main.h"
#include <stdio.h>	//delete

static void	free_array(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free (array);
}

static void	free_tasklist(t_tasks *tasklist, int n)
{
	t_tasks	*empty;

	while (n-- > 0)
	{
		tasklist->task_no = 0;
		free_array(tasklist->cmd_args);
		tasklist->cmd_args = NULL;
		tasklist->input_fd = 0;
		tasklist->output_fd = 0;
		empty = tasklist;
		tasklist = tasklist->next;
		free(empty);
	}
}

void	free_and_close(t_tasks *tasklist, char **paths, t_fds fds, int n)
{
	free_array(paths);
	free_tasklist(tasklist, n);
	open_close_pipes(&fds, CLOSE);
	close(fds.infile_fd);	// delete?
	close(fds.outfile_fd);	// delete?
}

void	error_and_exit(int error_code)
{
	if (error_code == INPUT_ERROR)
		printf("Error: too few arguments\n");
	exit(0);
}

void	checkleaks(void)
{
	system("leaks pipex");
}

int	main(int argc, char **argv, char **envp)
{
	char	**paths;
	t_fds	fds;
	pid_t	id;
	t_tasks	*task;
	int		cmd_no;

	if (argc < 5)
		error_and_exit(INPUT_ERROR);
	paths = get_paths(envp);
	task = create_tasklist(argc, &fds, argv);
	id = 1;
	cmd_no = 0;
	while (task->task_no > cmd_no)
	{
		if (id > 0)
		{
			cmd_no++;
			id = fork();
			if (id < 0)
				perror("Fork");
		}
		if (id == 0 && cmd_no == task->task_no)
			perform_task(task, paths, envp, fds);
		/* PROBABLY MOVE THIS PART SOMEWHERE ELSE */
		wait(0);
		close(task->input_fd);
		close(task->output_fd);
		/*  */
		task = task->next;
	}
	if (id > 0)
	{
		// atexit(checkleaks);
		while (wait(NULL) > 0);	// waitpid?
		free_and_close(task, paths, fds, cmd_no);
	}
	return (0);
}
