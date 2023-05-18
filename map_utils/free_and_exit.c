/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechaoub <aechaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 21:42:06 by kboughal          #+#    #+#             */
/*   Updated: 2023/05/18 14:58:35 by aechaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_and_exit(char **split_line, char **options_check, \
						char **options_list, char **wow)
{
	printf("Wrong Map DATA\n");
	free(split_line);
	free(options_check);
	free(options_list);
	free_split(wow);
	exit (1);
}

void	textures_naming_err(char **options_check, char **options_list)
{
	if (!check_all_elem(options_check))
	{
		printf("ERROR with textures data\n");
		free_split(options_list);
		free_split(options_check);
		exit(0);
	}
}

void	free_g_map(int **map, int tail)
{
	int	i;

	i = 0;
	while (i < tail)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	fillmap_exit(char **map, t_map_info *data)
{
	free_g_map(data->map, data->y_map_size);
	free_split(map);
	printf("Error  number of content \n");
	exit(0);
}
