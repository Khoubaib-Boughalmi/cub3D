/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_handler_P_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechaoub <aechaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:03:50 by aechaoub          #+#    #+#             */
/*   Updated: 2023/05/18 19:20:03 by aechaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_for_keys_w_s(t_vars *vars, t_key_value *info, int for_w)
{
	if (for_w)
	{
		info->speed = 1.5;
		if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT_SHIFT))
			info->speed = 3;
		info->x = (int)floor((vars->player.x + (vars->player.dx * 3)) / 64);
		info->y = (int)floor((vars->player.y + (vars->player.dy * 3)) / 64);
		info->xcheck = (int)floor((vars->player.x + (vars->player.dx)) / 64);
		info->ycheck = (int)floor((vars->player.y + (vars->player.dy)) / 64);
		info->factx = (int)floor((vars->player.x) / 64);
		info->facty = (int)floor((vars->player.y) / 64);
		return ;
	}
	info->x = (int)floor((vars->player.x - (vars->player.dx * 2)) / 64);
	info->y = (int)floor((vars->player.y - (vars->player.dy * 2)) / 64);
	info->xcheck = (int)floor((vars->player.x - (vars->player.dx)) / 64);
	info->ycheck = (int)floor((vars->player.y - (vars->player.dy)) / 64);
	info->factx = (int)floor((vars->player.x) / 64);
	info->facty = (int)floor((vars->player.y) / 64);
}

void	for_key_w(t_vars *vars)
{
	t_key_value	info;

	init_for_keys_w_s(vars, &info, 1);
	if (vars->map.map[info.y][info.x] <= 0
		&& vars->map.map[info.ycheck][info.xcheck] <= 0)
	{
		if (!(info.x != info.factx && info.y != info.facty
				&& vars->map.map[info.y][info.factx] > 0
			&& vars->map.map[info.facty][info.x] > 0))
		{
			vars->player.x += vars->player.dx * info.speed;
			vars->player.y += vars->player.dy * info.speed;
		}
	}
	else
	{
		if (vars->map.map[info.facty][info.x] <= 0
			&& vars->map.map[info.facty][info.xcheck] <= 0)
			vars->player.x += vars->player.dx;
		else if (vars->map.map[info.y][info.factx] <= 0
				&& vars->map.map[info.ycheck][info.factx] <= 0)
			vars->player.y += vars->player.dy;
	}
}

void	for_key_s(t_vars *vars)
{
	t_key_value	info;

	init_for_keys_w_s(vars, &info, 0);
	if (vars->map.map[info.y][info.x] <= 0
		&& vars->map.map[info.ycheck][info.xcheck] <= 0)
	{
		if (!(info.x != info.factx && info.y != info.facty
				&& vars->map.map[info.y][info.factx] > 0
			&& vars->map.map[info.facty][info.x] > 0))
		{
			vars->player.x -= vars->player.dx;
			vars->player.y -= vars->player.dy;
		}
	}
	else
	{
		if (vars->map.map[info.facty][info.x] <= 0
			&& vars->map.map[info.facty][info.xcheck] <= 0)
			vars->player.x -= vars->player.dx;
		else if (vars->map.map[info.y][info.factx] <= 0
				&& vars->map.map[info.ycheck][info.factx] <= 0)
			vars->player.y -= vars->player.dy;
	}
}
