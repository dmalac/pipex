/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   files_operations.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/16 12:01:11 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/08/18 18:34:50 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>

int	get_infile_fd(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		perror(filename);
	return (fd);
}

int	get_outfile_fd(char *filename)
{
	int	fd;

	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | \
	S_IRGRP | S_IROTH);
	if (fd < 0)
		perror(filename);
	return (fd);
}
