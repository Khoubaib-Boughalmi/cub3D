/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechaoub <aechaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:14:03 by kboughal          #+#    #+#             */
/*   Updated: 2023/05/19 16:36:40 by aechaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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

void	mouse_handler(double xpos, double ypos, void *param)
{
	t_vars	*vars;

	vars = (t_vars *)param;
	(void)ypos;
	if (xpos > vars->player.prev_xpos)
	{
		vars->player.angle += 0.07;
		if (vars->player.angle > 2 * M_PI)
			vars->player.angle -= 2 * M_PI;
		vars->player.dx = 5 * cos(vars->player.angle);
		vars->player.dy = 5 * sin(vars->player.angle);
	}
	if (xpos < vars->player.prev_xpos)
	{
		vars->player.angle -= 0.07;
		if (vars->player.angle < 0)
			vars->player.angle += 2 * M_PI;
		vars->player.dx = 5 * cos(vars->player.angle);
		vars->player.dy = 5 * sin(vars->player.angle);
	}
	vars->player.prev_xpos = xpos;
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
