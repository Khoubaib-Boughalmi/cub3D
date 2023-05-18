/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechaoub <aechaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:58:19 by aechaoub          #+#    #+#             */
/*   Updated: 2023/05/18 20:19:47 by aechaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int32_t	collect_color(uint8_t *pixels, int index)
{
	int32_t	color;

	color = create_color(pixels[index],
			pixels[index + 1],
			pixels[index + 2],
			pixels[index + 3]);
	return (color);
}

void	draw_it(t_vars *vars, t_draw_value *info, int lineH)
{
	int	i;
	int	y;

	i = -1;
	while (++i < 2)
	{
		info->in = 0;
		info->rl = info->y2;
		y = info->y1 - 3;
		while (++y <= lineH + (int)info->ligne_offset && y < 1023)
		{
			info->in = 512 * 4 * (int)floor(info->rl);
			if (info->theline + info->in < (int)info->imgtxet->height
				* (int)info->imgtxet->width * 4)
				info->color = collect_color(info->imgtxet->pixels,
						(info->theline) + info->in);
			else
				info->color = create_color(0, 0, 0, 0);
			mlx_put_pixel(vars->img, info->x1 - i, y, info->color);
			info->rl += info->g;
		}
	}
}

void	decide_horizontal_textures(t_vars *vars, t_draw_value *info, int rx)
{
	if (vars->player.x > rx)
		info->imgtxet = vars->EA_wall_texture;
	else
		info->imgtxet = vars->WE_wall_texture;
	if (vars->player.angle > PI / 2 && vars->player.angle < 3 * PI / 2)
		info->porcentsage = 1 - info->porcentsage;
}

void	decide_vertical_textures(t_vars *vars, t_draw_value *info, int ry)
{
	if (vars->player.y > ry)
		info->imgtxet = vars->NO_wall_texture_texture;
	else
		info->imgtxet = vars->SO_wall_texture;
	if (vars->player.angle < PI)
		info->porcentsage = 1 - info->porcentsage;
}

int	draw_wall_data(t_draw_value *info, int lineH)
{
	info->k = lineH;
	if (lineH > 1020)
		lineH = 1020;
	info->ligne_offset = 512 - lineH / 2;
	info->y1 = 512 - lineH / 2;
	info->y2 = (float)(info->k / 2 - 512) / info->k * 512;
	if (info->y2 < 0)
		info->y2 = 0;
	return (lineH);
}

void	draw_wall(t_vars *vars,  t_ray_info	ray, double lineH,
		int hororver)
{
	t_draw_value	info;

	if (hororver == 1)
		info.porcentsage = ray.ry / 64;
	if (hororver == 0)
		info.porcentsage = ray.rx / 64;
	info.porcentsage -= (int)info.porcentsage;
	info.x1 = ray.ray * 2 + 2;
	lineH = draw_wall_data(&info, lineH);
	if (vars->map.map[(int)floor(ray.ry / 64)][(int)floor(ray.rx / 64)] == 500)
		info.imgtxet = vars->door_texture;
	else if (hororver == 0)
		decide_vertical_textures(vars, &info, ray.ry);
	else if (hororver == 1)
		decide_horizontal_textures(vars, &info, ray.rx);
	info.theline = (int)(info.porcentsage * 512);
	info.theline *= 4;
	info.g = (float)512 / info.k;
	info.rl = 0;
	info.in = 0;
	draw_it(vars, &info, lineH);
}
