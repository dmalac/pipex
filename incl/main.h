/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/16 12:03:26 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/08/18 17:58:47 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdlib.h>

typedef struct s_tasks
{
	int				task_no;
	char			**cmd_args;
	int				input_fd;
	int				output_fd;
	struct s_tasks	*next;
}					t_tasks;

typedef struct s_fds
{
	int	infile_fd;
	int	outfile_fd;
	int	pipe_end[2][2];
}				t_fds;

# define OPEN 0
# define CLOSE 1

/* main.c */
void	error_and_exit(void);
/* setup.c */
char	**get_paths(void);
void	open_close_pipes(t_fds *fds, int instruction);
t_tasks	*create_tasklist(int argc, t_fds fds, char **argv);
void	get_fds(t_fds *fds, char *infile, char *outfile);
/* list_operations.c */
t_tasks	*lst_new(size_t i, size_t no_of_children, t_fds fds, char **argv);
void	lst_add_back(t_tasks **lst, t_tasks *new);
void	lst_print(t_tasks *lst);	// to be deleted
/* files_operations.c */
int		get_infile_fd(char *filename);
int		get_outfile_fd(char *filename);

#endif