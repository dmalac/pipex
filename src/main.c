/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/11 16:50:10 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/08/18 18:14:23 by dmalacov      ########   odam.nl         */
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

static void	free_tasklist(t_tasks *tasks)
{
	t_tasks	*empty;

	while (tasks)
	{
		tasks->task_no = 0;
		free_array(tasks->cmd_args);
		tasks->cmd_args = NULL;
		tasks->input_fd = 0;
		tasks->output_fd = 0;
		empty = tasks;
		tasks = tasks->next;
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
	// pid_t	id;
	t_tasks	*tasks;

	paths = get_paths();	// COULD BE NULL
	get_fds(&fds, argv[1], argv[argc - 1]);
	tasks = create_tasklist(argc, fds, argv);
	/* while loop - while task!= NULL */
		/* PARENT
			if task_no == 1 || id != 0 -> fork id */
		/* CHILD
			figure out what the input is
			close pipe[w] if necessary
			read from input
			close fd
			prepare cmd
			perform cmd
			write output to the correct fd (if pipe: close pipe[r])
			close fd */
		/* t_tasks tasks->next */

	// if (id > 0)
		// atexit(checkleaks);
	lst_print(tasks);
	free_array(paths);
	free_tasklist(tasks);
	open_close_pipes(&fds, CLOSE);
	close(fds.infile_fd);
	close(fds.outfile_fd);
	return (0);
}
