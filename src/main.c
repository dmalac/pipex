/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/11 16:50:10 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/08/18 20:01:11 by dmalacov      ########   odam.nl         */
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

static void	free_tasklist(t_tasks *tasklist, int process)
{
	t_tasks	*empty;

	while (process-- > 0)
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

void	error_and_exit(void)
{

}

void	checkleaks(void)
{
	system("leaks pipex");
}

int	main(int argc, char **argv)
{
	char	**paths;
	t_fds	fds;
	pid_t	id;
	t_tasks	*task;
	int		process;	//remove

	paths = get_paths();	// COULD BE NULL
	task = create_tasklist(argc, &fds, argv);
	id = 1;
	process = 0;
	while (task->task_no > process)
	{
		if (id > 0)
		{
			process++;	// remove
			id = fork();
			if (id < 0)
				perror("Fork");
		}
		if (id == 0 && process == task->task_no)
			perform_task(task, paths, process);	//remove process
		task = task->next;
	}

	if (id > 0)
	{
		// atexit(checkleaks);
		//PUT ALL THIS IN ONE FUNCTION FREE_EVERYTHING (TASK, PATHS, FDS, PROCESS)
		while (wait(NULL) > 0);
		lst_print(task);
		free_array(paths);
		free_tasklist(task, process);
		open_close_pipes(&fds, CLOSE);
		close(fds.infile_fd);
		close(fds.outfile_fd);
	}
	printf("%d: I'm done.\n", id);
	// if (id > 0)
	// 	while(1);
	return (0);
}
