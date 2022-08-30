/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/31 17:57:04 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/08/30 19:17:23 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft_bonus.h"

char	*create_line(char *line, struct s_data *data)
{
	int		j;
	char	*new;
	char	*temp;

	j = 0;
	while (data->buffer[data->i + j] && data->buffer[data->i + j] != '\n')
		j++;
	if (!line)
		line = ft_substr(data->buffer, (unsigned int)data->i, (size_t)(j + 1));
	else
	{
		new = ft_substr(data->buffer, (unsigned int)data->i, (size_t)(j + 1));
		temp = line;
		line = ft_strjoin(line, new);
		free(temp);
		free(new);
	}
	if (data->buffer[data->i + j])
		j++;
	data->i += j;
	return (line);
}

ssize_t	read_into_buffer(int fd, struct s_data *data)
{
	ssize_t	result;

	result = read(fd, data->buffer, BUFFER_SIZE);
	if (result >= 0)
		data->buffer[result] = '\0';
	data->i = 0;
	return (result);
}

void	free_all(char **buffer)
{
	if (*buffer)
	{
		if (!*buffer[0])
			*buffer[0] = 'x';
		free(*buffer);
	}
	*buffer = NULL;
}

char	*create_buffer(int len)
{
	char	*buffer;

	buffer = malloc(sizeof(char) * (len));
	if (buffer)
		ft_bzero(buffer, (size_t)len);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static struct s_data	data;
	char					*line;
	ssize_t					result;

	line = NULL;
	result = 1;
	while (result != 0 || data.buffer[data.i])
	{
		if (!data.buffer)
			data.buffer = create_buffer(BUFFER_SIZE + 1);
		if (data.buffer && !data.buffer[data.i])
			result = read_into_buffer(fd, &data);
		if (data.buffer && data.buffer[data.i])
			line = create_line(line, &data);
		if (!line || !data.buffer || result < 0)
		{
			free_all(&data.buffer);
			return (line);
		}
		if (line[ft_strlen(line) - 1] == '\n')
			return (line);
	}
	free_all(&data.buffer);
	return (line);
}
