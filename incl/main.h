/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/16 12:03:26 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/08/30 19:06:09 by dmalacov      ########   odam.nl         */
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

# define BEFORE 0
# define AFTER 1

# define INPUT_ERROR -1
# define INIT_ERROR -2
# define PARSING_ERROR -3
# define CMD_ERROR -4

# define W 1
# define R 0

/* cleanup.c */
void	free_array(char **array);
void	cleanup(t_tools *tools);
int		print_error_message(int error_code, char *name);
void	error_and_exit(int error_code, t_tools *tools, char *name);
/* parent.c */
char	**get_paths(char **environ);
t_tools	*tools_init(int argc, char **envp);
void	pipe_and_fork(int *id, t_tools *tools, int (*pipe_ends)[2]);
void	close_unnecessary_pipes(t_tools *tools, int pipe_end[2][2]);
int		wait_for_last_child(int id, size_t total_cmds);
/* child.c */
void	perform_cmd(t_tools *tools, char **argv, int pipe[2][2], char **envp);
/* files_operations.c */
int		get_infile_fd(char *filename);
int		get_outfile_fd(char *filename);

#endif