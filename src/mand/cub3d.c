/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 20:46:24 by kboughal          #+#    #+#             */
/*   Updated: 2023/05/19 19:58:08 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

t_vars				*g_vars;

void	randomize_the_sprites_texture(int sprite, int i)
{
	if (i % 2 == 0)
		g_vars->sprites[sprite].path = \
		ft_strdup("./textures/sprites/");
	else
		g_vars->sprites[sprite].path = \
		ft_strdup("./textures/sprites/g");
}

void	randomize_the_sprites(t_map_info *data)
{
	int	i;
	int	j;
	int	sprite;

	i = -1;
	sprite = 0;
	g_vars->numerof_sprite = data->number_of_sprites;
	g_vars->sprites = malloc(sizeof(t_sprite) * g_vars->numerof_sprite);
	while (++i < data->y_map_size)
	{
		j = -1;
		while (++j < data->x_map_size)
		{
			if (data->map[i][j] == -2 && sprite < 15)
			{
				g_vars->sprites[sprite].x = 64 * j + 32;
				g_vars->sprites[sprite].y = 64 * i + 32;
				randomize_the_sprites_texture(sprite, i);
				data->map[i][j] = 0;
				sprite++;
			}
		}
	}
}

int	main(int argc, char **argv)
{
	t_map_info	data;

	if (argc != 2)
	{
		printf("map required\n");
		exit (1);
	}
	cool(argv, &data);
	if (!init_vars(&data))
		return (0);
	render_window(g_vars);
	return (0);
}
