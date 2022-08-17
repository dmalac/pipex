/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_operations.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/17 20:15:25 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/08/17 20:25:29 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdlib.h>

t_tasks	*lst_new(size_t i, int no_of_children, int pipe_end[2][2], char **argv)
{
	t_tasks	*tasks;

	tasks = malloc(sizeof(t_tasks));
	if (tasks)
	{
		tasks->task_no = i;
		if (i == 1)
			tasks->input_fd = get_infile_fd(argv[1]);
		else
			tasks->input_fd = pipe_end[(i % 2) == 1][0];
		if (i == no_of_children)
			tasks->output_fd = get_outfile_fd(argv[no_of_children + 2]);
		else
			tasks->output_fd = pipe_end[(i % 2 == 0)][1];
		tasks->args = ft_split(argv[i + 1], ' ');
		if (!tasks->args)
			error_and_exit();	// figure out how to free everything
		tasks->cmd = tasks->args[0];
		tasks->next = NULL;
	}
	return (tasks);
}

void	lst_add_back(t_tasks **lst, t_tasks *new)
{
	
}
