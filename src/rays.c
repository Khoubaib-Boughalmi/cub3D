/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:08:47 by kboughal          #+#    #+#             */
/*   Updated: 2023/05/19 16:03:01 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	check_for_wall(t_vars *vars, t_ray_info *ray, t_wall *wall)
{
	while (ray->dof < 100)
	{
		ray->mx = (int)(ray->rx) / 64;
		ray->my = (int)(ray->ry) / 64;
		if (ray->mx >= 0 && ray->my >= 0 && ray->mx < vars->map.width \
		&& ray->my < vars->map.height && vars->map.map[ray->my][ray->mx] >= 1)
		{
			*wall->x_val = ray->rx;
			*wall->y_val = ray->ry;
			*wall->dist = distance_to_wall(vars->player.x, vars->player.y, \
			*wall->x_val, *wall->y_val);
			break ;
		}
		else
		{
			ray->rx += ray->xo;
			ray->ry += ray->yo;
			ray->dof++;
		}
	}
}

void	ft_initializer(t_vars *vars, t_ray_info *ray, t_wall *wall)
{
	ray->dof = 0;
	*wall->dist = 100000;
	*wall->x_val = vars->player.x;
	*wall->y_val = vars->player.y;
}

void	calculate_ver_intersect(t_vars *vars, t_ray_info *ray)
{	
	t_wall	wall;

	set_initial_vwall_value(vars, ray, &wall);
	ray->nTan = -tan(ray->ra);
	if (ray->ra > PI2 && ray->ra < PI3)
	{
		ray->rx = (((int)vars->player.x / 64) * 64) - 0.0001;
		ray->ry = (vars->player.x - ray->rx) * ray->nTan + vars->player.y;
		ray->xo = -64;
		ray->yo = -ray->xo * ray->nTan;
	}
	if (ray->ra < PI2 || ray->ra > PI3)
	{
		ray->rx = (((int)vars->player.x / 64) * 64) + 64;
		ray->ry = (vars->player.x - ray->rx) * ray->nTan + vars->player.y;
		ray->xo = 64;
		ray->yo = -ray->xo * ray->nTan;
	}
	if (ray->ra == PI2 || ray->ra == PI3)
	{
		ray->rx = vars->player.x;
		ray->ry = vars->player.y;
		ray->dof = 100;
	}
	check_for_wall(vars, ray, &wall);
}

void	calculate_hor_intersect(t_vars *vars, t_ray_info *ray)
{
	t_wall	wall;

	set_initial_hwall_value(vars, ray, &wall);
	ray->aTan = -1 / tan(ray->ra);
	if (ray->ra > PI)
	{
		ray->ry = (((int)vars->player.y / 64) * 64) - 0.0001;
		ray->rx = (vars->player.y - ray->ry) * ray->aTan + vars->player.x;
		ray->yo = -64;
		ray->xo = -ray->yo * ray->aTan;
	}
	if (ray->ra < PI)
	{
		ray->ry = (((int)vars->player.y / 64) * 64) + 64;
		ray->rx = (vars->player.y - ray->ry) * ray->aTan + vars->player.x;
		ray->yo = 64;
		ray->xo = -ray->yo * ray->aTan;
	}
	if (ray->ra == 0 || ray->ra == PI)
	{
		ray->rx = vars->player.x;
		ray->ry = vars->player.y;
		ray->dof = 100;
	}
	check_for_wall(vars, ray, &wall);
}

void	get_shortest_intersection(t_vars *vars, t_ray_info *ray, int i)
{
	t_line	line;

	if (ray->v_dist < ray->h_dist)
	{
		ray->rx = ray->v_x;
		ray->ry = ray->v_y;
		ray->f_dist = ray->v_dist;
	}
	else
	{
		ray->rx = ray->h_x;
		ray->ry = ray->h_y;
		ray->f_dist = ray->h_dist;
	}
	line.x0 = (vars->player.x * 16) / 64;
	line.y0 = (vars->player.y * 16) / 64;
	line.x1 = (ray->rx * 16) / 64;
	line.y1 = (ray->ry * 16) / 64;
	line.map_height = vars->img->height;
	line.map_width = vars->img->width;
	line.color = create_color(255, 255, 0, 255);
	g_ray_ds[i] = ray->f_dist;
	if (vars->keyboard.show_map)
		put_line(&line);
}
