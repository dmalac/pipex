/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_operations.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/17 20:15:25 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/08/22 14:45:00 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

t_tasks	*lst_new(size_t task_no, size_t no_of_children, t_fds fds, char **argv)
{
	t_tasks	*tasks;

	tasks = malloc(sizeof(t_tasks));
	if (tasks)
	{
		tasks->task_no = task_no;
		if (task_no == 1)
			tasks->input_fd = fds.infile_fd;
		else
			tasks->input_fd = fds.pipe_end[(task_no % 2) == 1][0];
		if (task_no == no_of_children)
			tasks->output_fd = fds.outfile_fd;
		else
			tasks->output_fd = fds.pipe_end[(task_no % 2 == 0)][1];
		tasks->cmd_args = ft_split(argv[task_no + 1], ' ');
		if (!tasks->cmd_args)
			error_and_exit(2);	// figure out how to free everything
		tasks->next = tasks;
	}
	return (tasks);
}

void	lst_add_back(t_tasks **lst, t_tasks *new)
{
	t_tasks	*current;

	if (!(*lst))
		*lst = new;
	else
	{
		current = *lst;
		while (current->next->task_no != 1)
			current = current->next;
		current->next = new;
		new->next = *lst;
	}
}

void	lst_print(t_tasks *lst)	// to be deleted
{
	int	i;

	while (lst->task_no < lst->next->task_no)
	{
		printf("task no. %d:\ncmd: %s\nargs: ", lst->task_no, lst->cmd_args[0]);
		i = 1;
		while (lst->cmd_args[i])
			printf("%s ", lst->cmd_args[i++]);
		printf("<%s>", lst->cmd_args[i]);
		printf("\ninput fd: %d\noutput fd: %d\n\n", lst->input_fd, lst->output_fd);
		lst = lst->next;
	}
	printf("task no. %d:\ncmd: %s\nargs: ", lst->task_no, lst->cmd_args[0]);
	i = 1;
	while (lst->cmd_args[i])
		printf("%s ", lst->cmd_args[i++]);
	printf("<%s>", lst->cmd_args[i]);
	printf("\ninput fd: %d\noutput fd: %d\n\n", lst->input_fd, lst->output_fd);
}
