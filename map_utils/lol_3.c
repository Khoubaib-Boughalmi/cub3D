/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lol_3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechaoub <aechaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:53:10 by aechaoub          #+#    #+#             */
/*   Updated: 2023/04/26 21:52:33 by aechaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	exitfunc(t_data *mapty)
{
	int	j;

	j = 0;
	while (j < mapty->map.y)
	{
		free(mapty->map.map[j]);
		j++;
	}
	free(mapty->map.map);
	write(1, "error.\n", 6);
	exit(0);
}

int	*addty(int len, char *g, int *map)
{
	int	i;

	i = 0;
	while (i < len - 1)
	{
		if (g[i] == '1')
			map[i] = 1;
		if (g[i] == '0')
			map[i] = 0;
		if (g[i] == 'C')
			map[i] = 5;
		if (g[i] == 'K')
			map[i] = 3;
		if (g[i] == 'E')
		{
			map[i] = 8;
		}
		if (g[i] == 'P')
		{
			map[i] = 7;
		}
		i++;
	}
	return (map);
}

int	add_toarr_2(t_data *mapty, int fd, int **map, t_val *val)
{
	char	*g;
	int		basiclen;

	val->i = 0;
	g = get_next_line(fd);
	basiclen = ft_strlen(g);
	while (g)
	{
		val->i = ft_strlen(g);
		if (val->i != basiclen)
		{
			if (!(get_next_line(fd) == 0 && basiclen - val->i == 1))
				exitfunc(mapty);
			val->i++;
		}
		map[val->j] = malloc(val->i * 8);
		addty(val->i, g, map[val->j]);
		val->j += 1;
		free(g);
		g = get_next_line(fd);
	}
	return (val->j);
}

int	add_toarr_3( int lines, int len, int **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < lines)
	{
		i = 0;
		while (i < len)
		{
			if (map[j][i] == 5 || map[j][i] == 8)
			{
				free_tab(map, 100);
			}
			i++;
		}
		j++;
	}
	return (i);
}

int	**add_toarr(t_data *mapty, char *av)
{
	int		fd;
	t_val	val;
	int		len;
	int		lines;
	int		**map;

	fd = open(av, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr("There is no map\n");
		exit (0);
	}
	val.i = 0;
	val.j = 0;
	map = malloc(50 * sizeof(int *));
	lines = add_toarr_2(mapty, fd, map, &val);
	len = val.i - 1;
	// planmap(map, len, lines);
	val.i = add_toarr_3(lines, len, map);
	close(fd);
	mapty->map.map = malloc((mapty->map.x + val.i - 1) * sizeof(int *));
	return (map);
}
