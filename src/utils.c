/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechaoub <aechaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 19:58:50 by kboughal          #+#    #+#             */
/*   Updated: 2023/05/18 19:23:19 by aechaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

double	ft_abs(double nb)
{
	if (nb < 0)
		return (-nb);
	return (nb);
}

void	put_line(int x0, int y0, int x1, int y1, int color, int map_width,
		int map_height)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	err2;

	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	sx = (x0 < x1) ? 1 : -1;
	sy = (y0 < y1) ? 1 : -1;
	err = dx - dy;
	while (x0 != x1 || y0 != y1)
	{
		if (x0 >= 0 && x0 < map_width && y0 >= 0 && y0 < map_height)
		{
			mlx_put_pixel(g_vars->img, x0, y0, color);
		}
		err2 = err * 2;
		if (err2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (err2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void	ft_recalibrate(double *ra)
{
	if (*ra < 0)
		*ra += 2 * PI;
	if (*ra > 2 * PI)
		*ra -= 2 * PI;
}