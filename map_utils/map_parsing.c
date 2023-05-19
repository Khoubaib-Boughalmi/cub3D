/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechaoub <aechaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 22:09:08 by aechaoub          #+#    #+#             */
/*   Updated: 2023/05/19 17:37:13 by aechaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "../libft/libft.h"
#include "get_next_line.h"
#include <math.h>
#include <stdio.h>

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

void	checkext(char *av)
{
	if (ft_strncmp(av + ft_strlen(av) - 4, ".cub", 5))
	{
		printf("The map description file must end with the .cub extension\n");
		exit(0);
	}
}

int	cool(char **av, t_map_info *data)
{
	char	*g;
	int		fd;
	char	**splited;
	char	**map;

	checkext(av[1]);
	fd = open(av[1], O_RDONLY);
	data->y_map_size = 0;
	data->x_map_size = 0;
	get_data_to_fill_texture_info(fd, data);
	g = skip_all_lines_before_the_map(fd);
	splited = get_the_map_from_file(g, fd, data);
	if (data->y_map_size > 42 || data->x_map_size > 42)
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
