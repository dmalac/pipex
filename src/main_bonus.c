/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_bonus.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/23 17:39:55 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/08/31 12:29:46 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main_bonus.h"
#include "libft_bonus.h"
#include <errno.h>
#include <unistd.h>

static void	write_prompt(size_t total_cmds)
{
	size_t	i;

	i = total_cmds - 3;
	while (i-- > 0)
		write(1, "pipe ", 5);
	write(1, "pipe heredoc> ", 14);
}

static size_t	heredoc(t_tools *tools, int (*pipe_end)[2], char *param, \
char *limiter)
{
	char	*line;

	line = NULL;
	if (ft_strncmp(param, "here_doc", 9) != 0)
		return (tools->cmd);
	if (pipe(pipe_end[0]) < 0)
		error_and_exit(errno, tools, NULL);
	write_prompt(tools->total_cmds);
	while (!line || (ft_strncmp(line, limiter, ft_strlen(limiter)) != 0 && \
	line[ft_strlen(limiter)] != '\n'))
	{
		if (line)
		{
			write(pipe_end[0][W], line, ft_strlen(line));
			free(line);
			write_prompt(tools->total_cmds);
		}
		line = get_next_line(0);
	}
	free(line);
	close(pipe_end[0][W]);
	tools->is_heredoc = 1;
	return (tools->cmd + 1);
}

int	main(int argc, char **argv, char **envp)
{
	pid_t	id;
	t_tools	*tools;
	int		pipe_end[2][2];
	int		exit_code;

	if (argc < 5)
		error_and_exit(INPUT_ERROR, NULL, NULL);
	tools = tools_init(argc, envp);
	id = 1;
	tools->cmd = heredoc(tools, pipe_end, argv[1], argv[2]);
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
