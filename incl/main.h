/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/16 12:03:26 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/08/17 20:34:38 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

typedef struct s_tasks
{
	int				task_no;
	char			*cmd;
	char			**args;
	int				input_fd;
	int				output_fd;
	struct s_tasks	*next;
}					t_tasks;

# define OPEN 0
# define CLOSE 1

/* main.c */
void	error_and_exit(void);
/* setup.c */
char	**get_paths(void);
void	open_close_pipes(int *(pipe_end[2][2]), int instruction);
t_tasks	*create_tasklist(int argc, int pipe_end[2][2], char **argv);
/* list_operations.c */
t_tasks	*lst_new(size_t i, int no_of_children, int pipe_end[2][2], char **argv);
void	lst_add_back(t_tasks **lst, t_tasks *new);
#endif