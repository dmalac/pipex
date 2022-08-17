/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/17 19:00:02 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/08/17 20:35:05 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "main.h"
#include "libft.h"

char	**get_paths(void)
{
	extern char	**environ;
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
			i = 0;
			while (paths[i])
			{
				temp = paths[i];
				paths[i] = ft_strjoin(paths[i], "/");
				free (temp);
				i++;
			}
		}
	}
	return (paths);
}

void	open_close_pipes(int *(pipe_end[2][2]), int instruction)
{
	if (instruction == OPEN)
	{
		if (pipe(pipe_end[0]) < 0 || pipe(pipe_end[1] < 0))
		{
			perror("Pipe error");
			error_and_exit();	// error handling to be fine-tuned
		}
	}
	else
	{
		close(pipe_end[0][0]);
		close(pipe_end[0][1]);
		close(pipe_end[1][0]);
		close(pipe_end[1][1]);
	}
}

t_tasks	*create_tasklist(int argc, int pipe_end[2][2], char **argv)
{
	t_tasks	*tasks;
	t_tasks	*new;
	int		no_of_children;
	size_t	i;

	i = 1;
	no_of_children = argc - 3;
	while (i <= no_of_children)
	{
		new = lst_new(i, no_of_children, pipe_end, argv);
		// can be NULL
		lst_add_back(&tasks, new);
		i++;
	}
	return (tasks);
}
