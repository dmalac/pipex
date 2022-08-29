/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   files_ops.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/16 12:01:11 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/08/29 10:58:20 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <fcntl.h>
#include <errno.h>

int	get_infile_fd(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY | O_CLOEXEC);
	if (fd < 0)
		print_error_message(errno, filename);
	return (fd);
}

int	get_outfile_fd(char *filename)
{
	int	fd;

	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		print_error_message(errno, filename);
	return (fd);
}
