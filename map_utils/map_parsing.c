/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 22:09:08 by aechaoub          #+#    #+#             */
/*   Updated: 2023/05/18 15:24:35 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "../libft/libft.h"
#include "get_next_line.h"
#include <math.h>
#include <stdio.h>

void	free_g_map(int **map, int till)
{
	int	i;

	i = 0;
	while (i < till)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

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

void	fillmap_exit(char **map, t_map_info *data)
{
	free_g_map(data->map, data->y_map_size);
	free_split(map);
	printf("Error  number of content \n");
	exit(0);
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
void	fill_texture_info(char **wow, t_map_info *data);

void	get_data_to_fill_texture_info(int fd, t_map_info *data)
{
	char	*trimed_str;
	int		i;
	char	*str_for_data;
	char	*g;
	int		nb;

	i = 0;
	str_for_data = ft_strdup("");
	g = get_next_line(fd);
	while (g)
	{
		trimed_str = ft_strtrim(g, "\n ");
		nb = ft_strlen(trimed_str);
		free(trimed_str);
		if (nb > 2)
			i++;
		str_for_data = ft_strjoin_gnl(str_for_data, g);
		free(g);
		if (i == 6)
			break ;
		g = get_next_line(fd);
	}
	fill_texture_info(ft_split(str_for_data, '\n'), data);
	free(str_for_data);
}

char	*skip_all_lines_before_the_map(int fd)
{
	char	*trimed_str;
	char	*g;
	int		nb;

	g = get_next_line(fd);
	while (g)
	{
		trimed_str = ft_strtrim(g, "\n ");
		nb = ft_strlen(trimed_str);
		free(trimed_str);
		if (nb > 2)
			break ;
		free(g);
		g = get_next_line(fd);
	}
	return (g);
}

char	**get_the_map_from_last_funct(t_map_info *data, char **splited)
{
	char	**map;
	int		i;
	int		j;

	i = -1;
	map = malloc(sizeof(char *) * (data->y_map_size + 1));
	while (splited[++i])
	{
		map[i] = malloc(data->x_map_size + 1);
		j = -1;
		while (splited[i][++j])
			map[i][j] = splited[i][j];
		free(splited[i]);
		while (j < data->x_map_size)
		{
			map[i][j] = ' ';
			j++;
		}
		map[i][j] = 0;
	}
	map[i] = 0;
	free(splited);
	return (map);
}

int	cool(char **av, t_map_info *data)
{
	char	*g;
	int		fd;
	char	**splited;
	char	**map;

	fd = open(av[1], O_RDONLY);
	data->y_map_size = 0;
	data->x_map_size = 0;
	get_data_to_fill_texture_info(fd, data);
	g = skip_all_lines_before_the_map(fd);
	splited = get_the_map_from_file(g, fd, data);
	if (data->y_map_size > 34 || data->x_map_size > 34)
	{
		printf("map too big\n");
		free_split(splited);
		exit(1);
	}
	map = get_the_map_from_last_funct(data, splited);
	check_walls(map, data);
	data->number_of_sprites = 0;
	fd = 0;
	fillmap(map, data, fd);
	return (0);
}
