/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:12:53 by kboughal          #+#    #+#             */
/*   Updated: 2023/05/19 16:02:17 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_map_info(t_map_info *data)
{
	g_vars->map_info.c_color.r = data->c_color.r;
	g_vars->map_info.c_color.g = data->c_color.g;
	g_vars->map_info.c_color.b = data->c_color.b;
	g_vars->map_info.f_color.b = data->f_color.b;
	g_vars->map_info.f_color.r = data->f_color.r;
	g_vars->map_info.f_color.g = data->f_color.g;
	g_vars->map_info.NO_texure = data->NO_texure;
	g_vars->map_info.SO_texure = data->SO_texure;
	g_vars->map_info.WE_texure = data->WE_texure;
	g_vars->map_info.EA_texure = data->EA_texure;
}

int	init_vars(t_map_info *data)
{
	g_vars = (t_vars *)malloc(sizeof(t_vars));
	if (!g_vars)
		return (0);
	g_vars->player.shoot = 0;
	g_vars->keyboard.show_map = 0;
	g_vars->player.bullet = 8;
	g_vars->window_info.height = 1024;
	g_vars->window_info.width = 1024;
	g_vars->map.map = data->map;
	g_vars->map.width = data->x_map_size;
	g_vars->map.height = data->y_map_size;
	g_vars->player.angle = data->angle_player * (PI / 180);
	g_vars->player.prev_xpos = 0;
	g_vars->player.x = data->x_player + 32;
	g_vars->player.y = data->y_player + 32;
	g_vars->player.dx = 5 * cos(g_vars->player.angle);
	g_vars->player.dy = 5 * sin(g_vars->player.angle);
	g_vars->keyboard.cursor = 0;
	init_map_info(data);
	return (1);
}

void	set_initial_hwall_value(t_vars *vars, t_ray_info *ray, t_wall *wall)
{	
	wall->x_val = &(ray->h_x);
	wall->y_val = &(ray->h_y);
	wall->dist = &(ray->h_dist);
	ft_initializer(vars, ray, wall);
}

void	set_initial_vwall_value(t_vars *vars, t_ray_info *ray, t_wall *wall)
{	
	wall->x_val = &(ray->v_x);
	wall->y_val = &(ray->v_y);
	wall->dist = &(ray->v_dist);
	ft_initializer(vars, ray, wall);
}
