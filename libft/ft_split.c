/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/26 12:02:38 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/08/25 19:17:28 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static void	erase_array(char **array, size_t i)
{
	size_t	j;

	j = 0;
	while (j <= i)
		free(array[j++]);
	free(array);
}

static char	*fill_array(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	str = (char *) malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	else
	{
		i = 0;
		if ((s[start] == '"' && s[start + len - 1] == '"') || \
		(s[start] == '\'' && s[start + len - 1] == '\''))
		{
			start++;
			len = len - 2;
		}
		while (i < len && s[start])
			str[i++] = s[start++];
		str[i] = '\0';
		return (str);
	}
}

static char	*cut_string(char const *s, char c, unsigned int *start)
{
	size_t	len;
	char	*str;
	char	q;

	len = 0;
	while (s[*start] == c)
		*start = *start + 1;
	while ((s[*start + len] != c) && s[*start + len])
	{
		if (s[*start + len] == '"' || s[*start + len] == '\'')
		{
			q = s[*start + len];
			len++;
			while (s[*start + len] != q && s[*start + len + 1])
				len++;
		}
		len++;
	}
	str = fill_array(s, *start, len);
	*start = *start + len;
	if (s[*start] == '"' || s[*start] == '\'')
		*start = *start + len;
	return (str);
}

static char	**make_frame(char const *s, char c, size_t *num_of_str)
{
	size_t	i;
	char	**array;
	char	q;

	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		while ((s[i] != c) && s[i])
		{
			if ((i == 0) || ((i > 0) && (s[i - 1] == c)))
				*num_of_str = *num_of_str + 1;
			if (s[i] == '"' || s[i] == '\'')
			{
				q = s[i];
				i++;
				while (s[i] != q && s[i + 1])
					i++;
			}
			i++;
		}
	}
	array = (char **) malloc((*num_of_str + 1) * sizeof(char *));
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char			**array;
	size_t			i;
	size_t			num_of_str;
	unsigned int	start;

	i = 0;
	start = 0;
	num_of_str = 0;
	if (s == NULL)
		return (NULL);
	array = make_frame(s, c, &num_of_str);
	if (array == NULL)
		return (NULL);
	while (i < num_of_str)
	{
		array[i] = cut_string(s, c, &start);
		if (array[i] == NULL)
		{
			erase_array(array, i);
			return (NULL);
		}
		i++;
	}
	array[i] = NULL;
	return (array);
}
