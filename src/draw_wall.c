/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:58:19 by aechaoub          #+#    #+#             */
/*   Updated: 2023/05/19 15:18:41 by kboughal         ###   ########.fr       */
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
