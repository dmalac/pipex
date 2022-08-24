/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/23 17:39:55 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/08/24 17:41:13 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "main.h"
#include "libft.h"
#include <stdio.h>		// delete (printf)

void	free_array(char **array)
{
	size_t	i;

	i = 0;
	while (array && array[i])
		free(array[i++]);
	free (array);
}

void	error_and_exit(int error_code)
{
	if (error_code == INPUT_ERROR)
		printf("Error: too few arguments\n");
	exit(0);
}

static void	cleanup(t_tools *tools)
{
	free_array(tools->paths);
	free_array(tools->cmd_args);
	free(tools);
}

void	checkleaks(void)
{
	system("leaks pipex");
}

int	main(int argc, char **argv, char **envp)
{
	pid_t	id;
	t_tools	*tools;
	int		pipe_end[2][2];

	if (argc < 5 && argv[1])
		error_and_exit(INPUT_ERROR);
	tools = tools_init(argc, envp);
	id = 1;
	while (tools->cmd < tools->total_cmds)
	{
		tools->cmd++;
		if (id > 0)
			pipe_and_fork(&id, tools->cmd, tools->total_cmds, pipe_end);
		if (id > 0)
			close_unnecessary_pipes(tools->cmd, pipe_end);
		if (id == 0)
			perform_cmd(tools, argv, pipe_end, envp);
	}
	cleanup(tools);
	while (id > 0 && wait(NULL))
		;
	return (0);
}

	// if (id > 0)
		// atexit(checkleaks);