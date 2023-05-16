/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechaoub <aechaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 19:58:50 by kboughal          #+#    #+#             */
/*   Updated: 2023/05/16 22:17:59 by aechaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

double ft_abs(double nb)
{
	if(nb < 0)
		return (-nb);
	return (nb);
}


// void put_line(void *mlx_ptr, void *win_ptr, int x0, int y0, int x1, int y1, int color)
// {
//     int dx = abs(x1 - x0); // Calculate absolute difference in x-coordinates
//     int dy = abs(y1 - y0); // Calculate absolute difference in y-coordinates
//     int sx = (x0 < x1) ? 1 : -1; // Determine the sign of x-increment
//     int sy = (y0 < y1) ? 1 : -1; // Determine the sign of y-increment
//     int err = dx - dy; // Initialize the error term

//     while (x0 != x1 || y0 != y1) {
//         mlx_put_pixel(g_vars->img , x0, y0, color); // Draw the current pixel

//         int err2 = err * 2; // Double the error term
//         if (err2 > -dy) {
//             err -= dy; // Update the error term
//             x0 += sx; // Move to the next x-coordinate
//         }
//         if (err2 < dx) {
//             err += dx; // Update the error term
//             y0 += sy; // Move to the next y-coordinate
//         }
//     }
// }

void put_line( int x0, int y0, int x1, int y1, int color, int map_width, int map_height)
{
    int dx = abs(x1 - x0); // Calculate absolute difference in x-coordinates
    int dy = abs(y1 - y0); // Calculate absolute difference in y-coordinates
    int sx = (x0 < x1) ? 1 : -1; // Determine the sign of x-increment
    int sy = (y0 < y1) ? 1 : -1; // Determine the sign of y-increment
    int err = dx - dy; // Initialize the error term

    while (x0 != x1 || y0 != y1) {
        // Check if the current pixel is within the map boundaries
        if (x0 >= 0 && x0 < map_width && y0 >= 0 && y0 < map_height) {
            mlx_put_pixel(g_vars->img , x0, y0, color); // Draw the current pixel
        }

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