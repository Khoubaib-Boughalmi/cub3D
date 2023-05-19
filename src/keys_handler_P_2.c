/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_handler_P_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechaoub <aechaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:18:57 by aechaoub          #+#    #+#             */
/*   Updated: 2023/05/19 16:09:30 by aechaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	for_key_f(t_vars *vars)
{
	if (vars->keyboard.cursor)
		mlx_set_cursor_mode(vars->mlx, MLX_MOUSE_NORMAL);
	else
		mlx_set_cursor_mode(vars->mlx, MLX_MOUSE_DISABLED);
	if (vars->keyboard.cursor)
		vars->keyboard.cursor = 0;
	else
		vars->keyboard.cursor = 1;
}

void	for_key_tab(t_vars *vars)
{
	if (vars->keyboard.show_map)
		vars->keyboard.show_map = 0;
	else
		vars->keyboard.show_map = 1;
}

void	for_key_space(t_vars *vars)
{
	int	factx;
	int	facty;
	int	x;
	int	y;
	int	i;

	factx = (int)floor((vars->player.x) / 64);
	facty = (int)floor((vars->player.y) / 64);
	x = factx;
	y = facty;
	i = 1;
	while (x == factx && y == facty)
	{
		x = (int)floor((vars->player.x + (vars->player.dx * i)) / 64);
		y = (int)floor((vars->player.y + (vars->player.dy * i)) / 64);
		i++;
	}
	if (vars->map.map[y][x] == 500)
		vars->map.map[y][x] = -10;
	else if (vars->map.map[y][x] == -10)
		vars->map.map[y][x] = 500;
}

int	key_press_handler_2(mlx_key_data_t keydata, void *param)
{
	t_vars	*vars;

	(void)keydata;
	vars = (t_vars *)param;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_SPACE))
		for_key_space(vars);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_R))
	{
		if (!vars->player.reload && vars->player.bullet != 8)
		{
			vars->player.reload = 42;
			vars->player.bullet = 8;
			show_gun_magazine(vars);
		}
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE)) // free shit
	{
		free_g_map(g_vars->map.map,g_vars->map.height);
		exit(0);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_TAB))
		for_key_tab(vars);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_F))
		for_key_f(vars);
	return (0);
}
