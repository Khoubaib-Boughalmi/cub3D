/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:44:22 by aechaoub          #+#    #+#             */
/*   Updated: 2023/05/15 17:15:27 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	checknl(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
		return (-1);
	return (i);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*p;

	i = 0;
	p = (char *)s;
	while (i < n)
	{
		p[i] = 0;
		i++;
	}
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*rtrnt(char **t)
{
	if (**t)
		return (*t);
	free(*t);
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*f;
	char		c[BUFFER_SIZE + 1];
	char		*t;
	int			y;
	int			red;

	red = 1;
	if (fd < 0)
		return (0);
	t = ft_strjoin_gnl(f, 0);
	f = 0;
	while (red > 0)
	{
		y = checknl(t);
		if (y != -1)
		{
			if (*(t + y + 1))
				f = ft_strdup(t + y + 1);
			return (ft_substr2(t, 0, y + 1));
		}
		ft_bzero(c, BUFFER_SIZE + 1);
		red = read(fd, c, BUFFER_SIZE);
		t = ft_strjoin_gnl(t, c);
	}
	return (rtrnt(&t));
}
