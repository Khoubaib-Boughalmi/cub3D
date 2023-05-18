/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:08:47 by kboughal          #+#    #+#             */
/*   Updated: 2023/05/18 21:33:56 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	check_for_wall(t_vars *vars, t_ray_info *ray, \
double *x_val, double *y_val, double *dist)
{
	while (ray->dof < 100)
	{
		ray->mx = (int)(ray->rx) / 64;
		ray->my = (int)(ray->ry) / 64;
		if (ray->mx >= 0 && ray->my >= 0 && ray->mx < vars->map.width \
		&& ray->my < vars->map.height && vars->map.map[ray->my][ray->mx] >= 1)
		{
			*x_val = ray->rx;
			*y_val = ray->ry;
			*dist = distance_to_wall(vars->player.x, vars->player.y, \
			*x_val, *y_val);
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

void	ft_initializer(t_vars *vars, t_ray_info *ray, double *x_val, \
double *y_val, double *dist)
{
	ray->dof = 0;
	*dist = 100000;
	*x_val = vars->player.x;
	*y_val = vars->player.y;
}

void	calculate_ver_intersect(t_vars *vars, t_ray_info *ray)
{	
	ft_initializer(vars, ray, &(ray->v_x), &(ray->v_y), &(ray->v_dist));
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
	check_for_wall(vars, ray, &ray->v_x, &ray->v_y, &ray->v_dist);
}

void	calculate_hor_intersect(t_vars *vars, t_ray_info *ray)
{
	ft_initializer(vars, ray, &(ray->h_x), &(ray->h_y), &(ray->h_dist));
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
	check_for_wall(vars, ray, &ray->h_x, &ray->h_y, &ray->h_dist);
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

void	draw_ray(t_vars *vars)
{
	t_ray_info	ray;
	// int			i;
	double		fish_eye_new_angle;
	double		line_height;

	ray.ray = 0;
	ray.ra = vars->player.angle - DEG * 30;
	ft_recalibrate(&(ray.ra));
	while (ray.ray < 512)
	{
		calculate_hor_intersect(vars, &ray);
		calculate_ver_intersect(vars, &ray);
		get_shortest_intersection(vars, &ray, ray.ray);
		fish_eye_new_angle = vars->player.angle - ray.ra;
		ft_recalibrate(&fish_eye_new_angle);
		ray.f_dist = ray.f_dist * cos(fish_eye_new_angle);
		line_height = (64 * 800) / ray.f_dist;
		if (ray.v_dist > ray.h_dist)
			draw_wall(vars,  ray, line_height, 0);
		else
			draw_wall(vars,  ray, line_height, 1);
		ray.ra = ray.ra + DEG / 8;
		ft_recalibrate(&(ray.ra));
		ray.ray++;
	}
}

