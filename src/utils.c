/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 19:58:50 by kboughal          #+#    #+#             */
/*   Updated: 2023/04/21 19:58:54 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

double ft_abs(double nb)
{
	if(nb < 0)
		return (-nb);
	return (nb);
}

void put_line(void *mlx_ptr, void *win_ptr, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0); // Calculate absolute difference in x-coordinates
    int dy = abs(y1 - y0); // Calculate absolute difference in y-coordinates
    int sx = (x0 < x1) ? 1 : -1; // Determine the sign of x-increment
    int sy = (y0 < y1) ? 1 : -1; // Determine the sign of y-increment
    int err = dx - dy; // Initialize the error term

    while (x0 != x1 || y0 != y1) {
        mlx_put_pixel(g_vars->img , x0, y0, 0x00FF00FF); // Draw the current pixel

        int err2 = err * 2; // Double the error term
        if (err2 > -dy) {
            err -= dy; // Update the error term
            x0 += sx; // Move to the next x-coordinate
        }
        if (err2 < dx) {
            err += dx; // Update the error term
            y0 += sy; // Move to the next y-coordinate
        }
    }
}