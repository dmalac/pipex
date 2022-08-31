/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   files_ops_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/16 12:01:11 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/08/31 12:29:35 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main_bonus.h"
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

int	get_outfile_fd(char *filename, int is_heredoc)
{
	int	fd;

	if (is_heredoc == 0)
		fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(filename, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		print_error_message(errno, filename);
	return (fd);
}
