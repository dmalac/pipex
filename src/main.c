/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/11 16:50:10 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/08/17 20:34:05 by dmalacov      ########   odam.nl         */
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
	int		pipe_end[2][2];
	// pid_t	id;
	t_tasks	*tasks;

	open_close_pipes(&pipe_end, OPEN);
	paths = get_paths();	// COULD BE NULL
	tasks = create_tasklist(argc, pipe_end, argv);
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
	// 	atexit(checkleaks);
	free_array(paths);
	open_close_pipes(&pipe_end, CLOSE);
	return (0);
}
