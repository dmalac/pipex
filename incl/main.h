/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/16 12:03:26 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/08/24 17:39:19 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdlib.h>

typedef struct s_tools
{
	size_t	cmd;
	size_t	total_cmds;
	int		input_fd;
	int		output_fd;
	char	**cmd_args;
	char	**paths;
}				t_tools;

# define OPEN 0
# define CLOSE 1

# define BEFORE 0
# define AFTER 1

# define INPUT_ERROR 1
# define INIT_ERROR 2
# define PIPE_ERROR 3
# define FORK_ERROR 4
# define OTHER_ERROR 9

# define W 1
# define R 0

/* main.c */
void	error_and_exit(int error_code);
void	free_array(char **array);
/* parent.c */
char	**get_paths(char **environ);
t_tools	*tools_init(int argc, char **envp);
void	pipe_and_fork(int *id, size_t cmd, size_t total_cmds, \
int (*pipe_ends)[2]);
void	close_unnecessary_pipes(size_t cmd, int pipe_end[2][2]);
/* child.c */
void	get_tools(t_tools *tools, char **argv, int pipe_end[2][2]);
char	*prepare_cmd(char *cmd, char **paths);
void	perform_cmd(t_tools *tools, char **argv, int pipe[2][2], char **envp);
void	close_pipes_child(size_t cmd, size_t total_cmds, int pipe_end[2][2], \
int when);
/* files_operations.c */
int		get_infile_fd(char *filename);
int		get_outfile_fd(char *filename);

#endif