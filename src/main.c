/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/23 17:39:55 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/08/30 19:00:27 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int argc, char **argv, char **envp)
{
	pid_t	id;
	t_tools	*tools;
	int		pipe_end[2][2];
	int		exit_code;

	if (argc != 5)
		error_and_exit(INPUT_ERROR, NULL, NULL);
	tools = tools_init(argc, envp);
	id = 1;
	while (tools->cmd <= tools->total_cmds)
	{
		if (id > 0)
			pipe_and_fork(&id, tools, pipe_end);
		if (id == 0)
			perform_cmd(tools, argv, pipe_end, envp);
		if (id > 0)
			close_unnecessary_pipes(tools, pipe_end);
		tools->cmd++;
	}
	cleanup(tools);
	exit_code = 0;
	if (id > 0)
		exit_code = wait_for_last_child(id, tools->total_cmds);
	return (exit_code);
}
