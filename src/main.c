/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/23 17:39:55 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/08/23 20:31:36 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>		// pid_t
#include "main.h"
#include <stdio.h>		// delete (printf)

static void	free_array(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free (array);
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
	pid_t	id;
	size_t	cmd_no;
	char	**paths;
	size_t	no_of_children;
	int		pipe_end[2][2];

	if (argc < 5)
		error_and_exit(INPUT_ERROR);
	no_of_children = argc - 3;
	paths = get_paths(envp);
	id = 1;
	cmd_no = 0;
	while (cmd_no < no_of_children)
	{
		cmd_no++;
		if (id > 0)
		{
			if (cmd_no < no_of_children)
				pipe(pipe_end[cmd_no % 2 == 0]);
			id = fork();
			if (id < 0)
				perror("Fork");	// replace with error_and_exit?
		}
		if (id > 0)
		{
			close(pipe_end[cmd_no % 2 == 0][W]);
			if (cmd_no > 1)
				close(pipe_end[(cmd_no - 1) % 2 == 0][R]);
			// while (1);
		}
		if (id == 0)
		{
			if (cmd_no < no_of_children)
				close(pipe_end[cmd_no % 2 == 0][R]);
			perform_cmd(cmd_no, argv, paths, envp, pipe_end);
		}
		/* 
		open necessary pipe
		fork
			-child does its thing
		close unnecessary end of pipe
		open necessary pipe
		fork
			-child does its thing
		close unnecessary end of pipe
		...
		 */
	}
	if (id > 0)
	{
		atexit(checkleaks);
		free_array(paths);
	}
	return (0);
}
