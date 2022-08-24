/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/11 13:32:12 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/08/15 12:15:24 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void	get_last_digit(int n, int fd)
{	
	char	c;

	if ((n / 10 != 0) || (n % 10 != 0))
	{
		get_last_digit(n / 10, fd);
		c = '0' - (n % 10);
		write(fd, &c, 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == 0)
		write(fd, "0", 1);
	else if (n < 0)
		write(fd, "-", 1);
	else
		n = n * -1;
	get_last_digit(n, fd);
}
