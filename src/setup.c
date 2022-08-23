/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/17 19:00:02 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/08/23 17:24:03 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "main.h"
#include "libft.h"

char	**get_paths(char **environ)
{
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

void	open_close_pipes(t_fds *fds, int instruction)
{
	if (instruction == OPEN)
	{
		if (pipe(fds->pipe_end[0]) < 0 || pipe(fds->pipe_end[1]) < 0)
		{
			perror("Pipe error");
			error_and_exit(2);	// error handling to be fine-tuned
		}
	}
	else
	{
		close(fds->pipe_end[0][0]);
		close(fds->pipe_end[0][1]);
		close(fds->pipe_end[1][0]);
		close(fds->pipe_end[1][1]);
	}
}

t_tasks	*create_tasklist(int argc, t_fds *fds, char **argv)
{
	t_tasks	*top;
	t_tasks	*new;
	size_t	no_of_children;
	size_t	i;

	i = 1;
	no_of_children = argc - 3;
	top = NULL;
	// get_fds(fds, argv[1], argv[argc - 1]);
	open_close_pipes(fds, OPEN);
	while (i <= no_of_children)
	{
		new = lst_new(i, no_of_children, *fds, argv);
		if (!new)
			printf("[create tasklist: sth went wrong with mallocing node no. %zu\n", i);
		lst_add_back(&top, new);
		i++;
	}
	return (top);
}

// void	get_fds(t_fds *fds, char *infile, char *outfile)
// {
// 	open_close_pipes(fds, OPEN);
// 	fds->infile_fd = -1;
// 	fds->outfile_fd = get_outfile_fd(outfile);
// }
