/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleanup_bonus.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/29 10:59:21 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/08/31 14:27:58 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include "main_bonus.h"
#include "libft_bonus.h"

void	free_array(char **array)
{
	size_t	i;

	i = 0;
	while (array && array[i])
	{
		free(array[i]);
		array[i++] = NULL;
	}
	free (array);
	array = NULL;
}

void	cleanup(t_tools *tools)
{
	free_array(tools->paths);
	free_array(tools->cmd_args);
	free(tools);
	tools = NULL;
}

int	print_error_message(int error_code, char *name)
{
	char	*error_message;	

	ft_putstr_fd("Error: ", 2);
	if (error_code == CMD_ERROR)
	{
		error_code = 127;
		ft_putstr_fd("Command not found", 2);
	}
	else
	{
		error_message = strerror(error_code);
		ft_putstr_fd(error_message, 2);
	}
	if (name)
	{
		write(2, ": ", 2);
		ft_putstr_fd(name, 2);
	}
	write(2, "\n", 1);
	return (error_code);
}

void	error_and_exit(int error_code, t_tools *tools, char *name)
{
	if (error_code == INPUT_ERROR)
	{
		ft_putstr_fd("Error: wrong number of arguments\n", 2);
		ft_putstr_fd("Required input format: ", 2);
		ft_putstr_fd("<file1> <cmd1> <cmd2> ... <cmdn> <file2>\n", 2);
	}
	else if (error_code == INIT_ERROR)
		ft_putstr_fd("Error: memory allocation failed\n", 2);
	else if (error_code == PARSING_ERROR)
		ft_putstr_fd("Error: argument parsing failed\n", 2);
	else
	{
		error_code = print_error_message(error_code, name);
		cleanup(tools);
	}
	if (error_code < 0)
		error_code = 1;
	if (error_code == 13)
		error_code = 126;
	exit(error_code);
}
