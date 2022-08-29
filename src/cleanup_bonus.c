/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleanup_bonus.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/29 10:59:21 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/08/29 14:16:33 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "main.h"
#include "libft.h"

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
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(name, 2);
	}
	ft_putstr_fd("\n", 2);
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
	exit(error_code);
}
