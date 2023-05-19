/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:14:03 by kboughal          #+#    #+#             */
/*   Updated: 2023/05/19 19:58:08 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	key_press_handler(void *param)
{
	t_vars	*vars;

	vars = (t_vars *)param;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
		for_key_right(vars);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
	{
		vars->player.angle -= 0.1;
		if (vars->player.angle < 0)
			vars->player.angle += 2 * M_PI;
		vars->player.dx = 5 * cos(vars->player.angle);
		vars->player.dy = 5 * sin(vars->player.angle);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_W))
		for_key_w(vars);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_S))
		for_key_s(vars);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_A))
		for_key_a(vars);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_D))
		for_key_d(vars);
	return (0);
}


void	loop_func(void *data)
{
	static int	frame = 0;
	t_vars		*vars;

	vars = (t_vars *)data;
	if (frame % 5 == 0)
		redraw(vars);
	if (frame > 10000)
		frame = 0;
	frame++;
}
