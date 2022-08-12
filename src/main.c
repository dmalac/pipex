/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/11 16:50:10 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/08/12 19:16:26 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../libft/libft.h"
#include <stdio.h>	//delete

char	**get_paths(void)
{
	extern char	**environ;
	char		**paths;
	int			i;

	i = 0;
	paths = NULL;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], "PATH=", 5) == 0)
		{
			paths = ft_split(environ[i] + 5, ':');
			return (paths);
		}
		i++;
	}
	return (paths);
}

int	main(int argc, char **argv)
{
	char	**paths;
	char	*infile;
	int		i;

	if (argc > 1)
		infile = argv[1];
	paths = get_paths();	// COULD BE NULL
	printf("PATHS:\n");
	i = 0;
	while (paths[i])
		printf("%s\n", paths[i++]);
	return (0);
}
