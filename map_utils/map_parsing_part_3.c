/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_part_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechaoub <aechaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 22:09:08 by aechaoub          #+#    #+#             */
/*   Updated: 2023/05/18 14:53:01 by aechaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "../libft/libft.h"
#include "get_next_line.h"
#include <math.h>
#include <stdio.h>

int	**allocate_map_memory(int y_size, int x_size)
{
	int	**map;
	int	i;

	i = 0;
	map = malloc(sizeof(int *) * y_size);
	while (i < y_size)
	{
		map[i] = malloc(sizeof(int) * x_size);
		i++;
	}
	return (map);
}

void	set_player_info(char cell, t_map_info *data, int i, int j)
{
	if (cell == 'N')
		data->angle_player = 270;
	else if (cell == 'S')
		data->angle_player = 90;
	else if (cell == 'W')
		data->angle_player = 180;
	else if (cell == 'E')
		data->angle_player = 0;
	data->x_player = j * 64;
	data->y_player = i * 64;
}

void	set_map_value(char **map, t_map_info *data, int i, int j)
{
	if (map[i][j] == '1')
		data->map[i][j] = 1;
	else if (map[i][j] == ' ')
		data->map[i][j] = -1;
	else if (map[i][j] == 'd')
		data->map[i][j] = 500;
	else if (map[i][j] == '0')
		data->map[i][j] = 0;
	else if (map[i][j] == '#')
	{
		if (data->number_of_sprites < 15)
			data->number_of_sprites++;
		data->map[i][j] = -2;
	}
	else
		fillmap_exit(map, data);
}

void	fillmap_kmala(char **map, t_map_info *data, int *player_mara)
{
	if (*player_mara == 1)
		fillmap_exit(map, data);
	(*player_mara)++;
}

void	fillmap(char **map, t_map_info *data, int player_mara)
{
	int	i;
	int	j;

	i = -1;
	data->map = allocate_map_memory(data->y_map_size, data->x_map_size);
	while (map[++i])
	{
		j = -1;
		while (++j < data->x_map_size)
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W'
				|| map[i][j] == 'E')
			{
				fillmap_kmala(map, data, &player_mara);
				data->map[i][j] = 0;
				set_player_info(map[i][j], data, i, j);
			}
			else
				set_map_value(map, data, i, j);
		}
	}
	if (player_mara == 0)
		fillmap_exit(map, data);
	free_split(map);
}
