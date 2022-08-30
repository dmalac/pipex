/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft_bonus.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmalacov <dmalacov@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/12 18:51:07 by dmalacov      #+#    #+#                 */
/*   Updated: 2022/08/30 19:17:33 by dmalacov      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_BONUS_H
# define LIBFT_BONUS_H

# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

struct	s_data
{
	char	*buffer;
	int		i;
};

void	ft_bzero(void *s, size_t n);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*get_next_line(int fd);

#endif