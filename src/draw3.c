/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:29:52 by kboughal          #+#    #+#             */
/*   Updated: 2023/05/19 15:30:15 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_ray(t_vars *vars)
{
	t_ray_info	ray;
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
			draw_wall(vars, ray, line_height, 0);
		else
			draw_wall(vars, ray, line_height, 1);
		ray.ra = ray.ra + DEG / 8;
		ft_recalibrate(&(ray.ra));
		ray.ray++;
	}
}
