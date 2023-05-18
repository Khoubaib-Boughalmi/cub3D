/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechaoub <aechaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 21:09:42 by aechaoub          #+#    #+#             */
/*   Updated: 2023/05/18 21:35:54 by aechaoub         ###   ########.fr       */
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

void	get_sprite_texture(int frame, char *sprite_path,
		mlx_texture_t **imgtxet)
{
	char	*str;
	char	*tmp;

	tmp = ft_itoa(frame / 2);
	str = ft_strjoin(sprite_path, tmp);
	free(tmp);
	tmp = str;
	str = ft_strjoin(str, ".png");
	(*imgtxet) = mlx_load_png(str);
	free(tmp);
	free(str);
}

void	draw_the_sprite_while_in_while(t_vars *vars, t_sp *sp,
		t_sprite_value *info)
{
	int	i;
	int	y;

	i = 0;
	while (i < 2)
	{
		info->tot_h = 0;
		info->suu = (int)info->tot_v * 4;
		info->lol = (int)(info->tot_h * 160 * 4) + info->suu;
		y = info->y1;
		while (y <= sp->line_height + (int)info->ligne_offset && y < 1024)
		{
			if (info->lol < (int)info->imgtxet->height
				* (int)info->imgtxet->width * 4)
				info->color = collect_color(info->imgtxet->pixels,
						info->lol);
			if (info->color != info->trans)
				mlx_put_pixel(vars->img, info->x1 - i, y, info->color);
			info->tot_h += info->por_h;
			info->lol = (int)info->tot_h * 160 * 4 + info->suu;
			y++;
		}
		info->tot_v += info->por_v;
		i++;
	}
}

void	draw_the_sprite_while(t_vars *vars, t_sp *sp, t_sprite_value *info)
{
	while (info->time < (int)sp->porce_angle + (sp->line_height / 10)
		&& info->time < 512)
	{
		if (sp->v_dist < g_ray_ds[info->time])
		{
			g_ray_ds[info->time] = sp->v_dist;
			info->x1 = info->time * 2 + 2;
			draw_the_sprite_while_in_while(vars, sp, info);
		}
		else
			info->tot_v += 2 * info->por_v;
		info->time++;
	}
}

void	draw_the_sprite(t_vars *vars, t_sp *sp, int frame, char *sprite_path)
{
	t_sprite_value	info;

	info.trans = create_color(0, 0, 0, 0);
	info.x1 = (int)sp->porce_angle * 2 + 2;
	if (sp->line_height > 1020)
		sp->line_height = 1020;
	info.ligne_offset = 512 - sp->line_height / 2.9;
	info.y1 = 512 - sp->line_height / 2.9;
	info.por_h = 608 / sp->line_height;
	info.tot_h = 0;
	info.por_v = 160 / (4 * sp->line_height / 10);
	info.tot_v = 0;
	info.lol = 0;
	info.suu = 0;
	info.time = sp->porce_angle - (sp->line_height / 10);
	if (info.time < 0)
	{
		info.tot_v += abs(info.time * 2) * info.por_v;
		info.time = 0;
	}
	get_sprite_texture(frame, sprite_path, &info.imgtxet);
	draw_the_sprite_while(vars, sp, &info);
	mlx_delete_texture(info.imgtxet);
}
