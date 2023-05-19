/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechaoub <aechaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:03:50 by aechaoub          #+#    #+#             */
/*   Updated: 2023/05/19 16:36:16 by aechaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	retate_handler(t_vars *vars, t_key_value *info)
{
	if (vars->map.map[info->y][info->x] <= 0
		&& vars->map.map[info->ycheck][info->xcheck] <= 0)
	{
		if (!(info->x != info->factx && info->y != info->facty
				&& vars->map.map[info->y][info->factx] > 0
			&& vars->map.map[info->facty][info->x] > 0))
		{
			vars->player.x += info->dxright;
			vars->player.y += info->dyright;
		}
	}
	else
	{
		if (vars->map.map[info->facty][info->x] <= 0
			&& vars->map.map[info->facty][info->xcheck] <= 0)
			vars->player.x += info->dxright;
		else if (vars->map.map[info->y][info->factx] <= 0
				&& vars->map.map[info->ycheck][info->factx] <= 0)
			vars->player.y += info->dyright;
	}
}

void	for_key_a(t_vars *vars)
{
	t_key_value	info;

	info.dxright = 5 * cos(vars->player.angle - M_PI / 2);
	info.dyright = 5 * sin(vars->player.angle - M_PI / 2);
	info.x = (int)floor((vars->player.x + (info.dxright * 3)) / 64);
	info.y = (int)floor((vars->player.y + (info.dyright * 3)) / 64);
	info.xcheck = (int)floor((vars->player.x + (info.dxright)) / 64);
	info.ycheck = (int)floor((vars->player.y + (info.dyright)) / 64);
	info.factx = (int)floor((vars->player.x) / 64);
	info.facty = (int)floor((vars->player.y) / 64);
	retate_handler(vars, &info);
}

void	for_key_d(t_vars *vars)
{
	t_key_value	info;

	info.dxright = 5 * cos(vars->player.angle + M_PI / 2);
	info.dyright = 5 * sin(vars->player.angle + M_PI / 2);
	info.x = (int)floor((vars->player.x + (info.dxright * 3)) / 64);
	info.y = (int)floor((vars->player.y + (info.dyright * 3)) / 64);
	info.xcheck = (int)floor((vars->player.x + (info.dxright)) / 64);
	info.ycheck = (int)floor((vars->player.y + (info.dyright)) / 64);
	info.factx = (int)floor((vars->player.x) / 64);
	info.facty = (int)floor((vars->player.y) / 64);
	retate_handler(vars, &info);
}

void	for_key_right(t_vars *vars)
{
	vars->player.angle += 0.1;
	if (vars->player.angle > 2 * M_PI)
		vars->player.angle -= 2 * M_PI;
	vars->player.dx = 5 * cos(vars->player.angle);
	vars->player.dy = 5 * sin(vars->player.angle);
}
