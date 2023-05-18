/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_part_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 22:09:08 by aechaoub          #+#    #+#             */
/*   Updated: 2023/05/18 15:19:58 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "../libft/libft.h"
#include "get_next_line.h"
#include <math.h>
#include <stdio.h>

void	check_walls_exit(char **map)
{
	free_split(map);
	printf("Error\n");
	exit(0);
}

int	check_walls(char **map, t_map_info *data)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] != '1' && map[y][x] != ' ')
			{
				if (y == 0 || map[y - 1][x] == ' ')
					check_walls_exit(map);
				if (x == 0 || map[y][x - 1] == ' ')
					check_walls_exit(map);
				if (y + 1 >= data->y_map_size || map[y + 1][x] == ' ')
					check_walls_exit(map);
				if (x + 1 >= data->x_map_size || map[y][x + 1] == ' ')
					check_walls_exit(map);
			}
		}
	}
	return (0);
}

int	get_the_map_from_file_help(char *g, int len, char *str, int shouldstop)
{
	if (g[len - 1] == '\n')
		len--;
	if (shouldstop || !len)
	{
		printf("error map_pars %d\n",len);
		free(g);
		free(str);
		exit(1);
	}
	return (len);
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

char	**get_the_map_from_file(char *g, int fd, t_map_info *data)
{
	int		shouldstop;
	int		len;
	char	*str;
	char	**splited;

	shouldstop = 0;
	str = ft_strdup("");
	while (g)
	{
		len = ft_strlen(g);
		len = get_the_map_from_file_help(g, len, str, shouldstop);
		if (len < 2)
			shouldstop = 1;
		data->x_map_size = ft_max(len, data->x_map_size);
		str = ft_strjoin_gnl(str, g);
		free(g);
		g = get_next_line(fd);
		data->y_map_size++;
	}
	splited = ft_split(str, '\n');
	free(str);
	return (splited);
}
