/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tasks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 18:49:30 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/08/18 19:17:24 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdio.h>	// delete

/* CHILD
			figure out what the input is
			close pipe[w] if necessary
			read from input
			close fd
			prepare cmd
			perform cmd
			write output to the correct fd (if pipe: close pipe[r])
			close fd */

void	perform_task(t_tasks *task, char **paths, int process)	//remove process
{
	int	i;

	printf("Child no. %d here. I was created to perform task no. %d\n", \
	process, task->task_no);
	if (paths)
		i = 1;
	else
		i = 2;
}
