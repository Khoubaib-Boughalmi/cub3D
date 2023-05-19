/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechaoub <aechaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 19:58:50 by kboughal          #+#    #+#             */
/*   Updated: 2023/05/19 16:36:06 by aechaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

double	ft_abs(double nb)
{
	if (nb < 0)
		return (-nb);
	return (nb);
}

void	brs_initialize(t_bresenham	*brs, t_line *line)
{
	brs->dx = abs(line->x1 - line->x0);
	brs->dy = abs(line->y1 - line->y0);
	if (line->x0 < line->x1)
		brs->sx = 1;
	else
		brs->sx = -1;
	if (line->y0 < line->y1)
		brs->sy = 1;
	else
		brs->sy = -1;
	brs->err = brs->dx - brs->dy;
}

void	put_line(t_line *line)
{
	t_bresenham	brs;

	brs_initialize(&brs, line);
	while (line->x0 != line->x1 || line->y0 != line->y1)
	{
		if (line->x0 >= 0 && line->x0 < line->map_width && \
		line->y0 >= 0 && line->y0 < line->map_height)
			mlx_put_pixel(g_vars->img, line->x0, line->y0, line->color);
		brs.err2 = brs.err * 2;
		if (brs.err2 > -brs.dy)
		{
			brs.err -= brs.dy;
			line->x0 += brs.sx;
		}
		if (brs.err2 < brs.dx)
		{
			brs.err += brs.dx;
			line->y0 += brs.sy;
		}
	}
}

void	ft_recalibrate(double *ra)
{
	if (*ra < 0)
		*ra += 2 * M_PI;
	if (*ra > 2 * M_PI)
		*ra -= 2 * M_PI;
}
