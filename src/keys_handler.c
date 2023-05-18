/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechaoub <aechaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:03:50 by aechaoub          #+#    #+#             */
/*   Updated: 2023/05/18 18:48:39 by aechaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	for_key_w(t_vars *vars)
{
	t_key_value	info;
	int			x;
	int			y;
	float		speed;

	speed = 1.5;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT_SHIFT))
		speed = 3;
	x = (int)floor((vars->player.x + (vars->player.dx * 3)) / 64);
	y = (int)floor((vars->player.y + (vars->player.dy * 3)) / 64);
	info.xcheck = (int)floor((vars->player.x + (vars->player.dx)) / 64);
	info.ycheck = (int)floor((vars->player.y + (vars->player.dy)) / 64);
	info.factx = (int)floor((vars->player.x) / 64);
	info.facty = (int)floor((vars->player.y) / 64);
	if (vars->map.map[y][x] <= 0
		&& vars->map.map[info.ycheck][info.xcheck] <= 0)
	{
		if (!(x != info.factx && y != info.facty
				&& vars->map.map[y][info.factx] > 0
			&& vars->map.map[info.facty][x] > 0))
		{
			vars->player.x += vars->player.dx * speed;
			vars->player.y += vars->player.dy * speed;
		}
	}
	else
	{
		if (vars->map.map[info.facty][x] <= 0
			&& vars->map.map[info.facty][info.xcheck] <= 0)
			vars->player.x += vars->player.dx;
		else if (vars->map.map[y][info.factx] <= 0
				&& vars->map.map[info.ycheck][info.factx] <= 0)
			vars->player.y += vars->player.dy;
	}
}

void	for_key_s(t_vars *vars)
{
	t_key_value	info;
	int			x;
	int			y;

	x = (int)floor((vars->player.x - (vars->player.dx * 2)) / 64);
	y = (int)floor((vars->player.y - (vars->player.dy * 2)) / 64);
	info.xcheck = (int)floor((vars->player.x - (vars->player.dx)) / 64);
	info.ycheck = (int)floor((vars->player.y - (vars->player.dy)) / 64);
	info.factx = (int)floor((vars->player.x) / 64);
	info.facty = (int)floor((vars->player.y) / 64);
	if (vars->map.map[y][x] <= 0
		&& vars->map.map[info.ycheck][info.xcheck] <= 0)
	{
		if (!(x != info.factx && y != info.facty
				&& vars->map.map[y][info.factx] > 0
			&& vars->map.map[info.facty][x] > 0))
		{
			vars->player.x -= vars->player.dx;
			vars->player.y -= vars->player.dy;
		}
	}
	else
	{
		if (vars->map.map[info.facty][x] <= 0
			&& vars->map.map[info.facty][info.xcheck] <= 0)
			vars->player.x -= vars->player.dx;
		else if (vars->map.map[y][info.factx] <= 0
				&& vars->map.map[info.ycheck][info.factx] <= 0)
			vars->player.y -= vars->player.dy;
	}
}

// void	retate_handler(t_vars *vars, int x, int y, int xcheck)
// {
// 	float	dxright;
// 	float	dyright;
// 	int		ycheck;
// 	int		factx;
// 	int		facty;
// 	if (vars->map.map[y][x] <= 0 && vars->map.map[ycheck][xcheck] <= 0)
// 	{
// 		if (!(x != factx && y != facty && vars->map.map[y][factx] > 0
// 			&& vars->map.map[facty][x] > 0))
// 		{
// 			vars->player.x += dxright;
// 			vars->player.y += dyright;
// 		}
// 	}

// }

void	for_key_a(t_vars *vars)
{
	t_key_value	info;
	int			x;
	int			y;

	info.dxright = 5 * cos(vars->player.angle - PI / 2);
	info.dyright = 5 * sin(vars->player.angle - PI / 2);
	x = (int)floor((vars->player.x + (info.dxright * 3)) / 64);
	y = (int)floor((vars->player.y + (info.dyright * 3)) / 64);
	info.xcheck = (int)floor((vars->player.x + (info.dxright)) / 64);
	info.ycheck = (int)floor((vars->player.y + (info.dyright)) / 64);
	info.factx = (int)floor((vars->player.x) / 64);
	info.facty = (int)floor((vars->player.y) / 64);
	if (vars->map.map[y][x] <= 0
		&& vars->map.map[info.ycheck][info.xcheck] <= 0)
	{
		if (!(x != info.factx && y != info.facty
				&& vars->map.map[y][info.factx] > 0
			&& vars->map.map[info.facty][x] > 0))
		{
			vars->player.x += info.dxright;
			vars->player.y += info.dyright;
		}
	}
	else
	{
		if (vars->map.map[info.facty][x] <= 0
			&& vars->map.map[info.facty][info.xcheck] <= 0)
			vars->player.x += info.dxright;
		else if (vars->map.map[y][info.factx] <= 0
				&& vars->map.map[info.ycheck][info.factx] <= 0)
			vars->player.y += info.dyright;
	}
}

void	for_key_d(t_vars *vars)
{
	t_key_value	info;
	int			x;
	int			y;

	info.dxright = 5 * cos(vars->player.angle + PI / 2);
	info.dyright = 5 * sin(vars->player.angle + PI / 2);
	x = (int)floor((vars->player.x + (info.dxright * 3)) / 64);
	y = (int)floor((vars->player.y + (info.dyright * 3)) / 64);
	info.xcheck = (int)floor((vars->player.x + (info.dxright)) / 64);
	info.ycheck = (int)floor((vars->player.y + (info.dyright)) / 64);
	info.factx = (int)floor((vars->player.x) / 64);
	info.facty = (int)floor((vars->player.y) / 64);
	if (vars->map.map[y][x] <= 0
		&& vars->map.map[info.ycheck][info.xcheck] <= 0)
	{
		if (!(x != info.factx && y != info.facty
				&& vars->map.map[y][info.factx] > 0
			&& vars->map.map[info.facty][x] > 0))
		{
			vars->player.x += info.dxright;
			vars->player.y += info.dyright;
		}
	}
	else
	{
		if (vars->map.map[info.facty][x] <= 0
			&& vars->map.map[info.facty][info.xcheck] <= 0)
			vars->player.x += info.dxright;
		else if (vars->map.map[y][info.factx] <= 0
				&& vars->map.map[info.ycheck][info.factx] <= 0)
			vars->player.y += info.dyright;
	}
}

void	for_key_right(t_vars *vars)
{
	vars->player.angle += 0.1;
	if (vars->player.angle > 2 * PI)
		vars->player.angle -= 2 * PI;
	vars->player.dx = 5 * cos(vars->player.angle);
	vars->player.dy = 5 * sin(vars->player.angle);
}
