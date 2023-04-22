/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 20:46:24 by kboughal          #+#    #+#             */
/*   Updated: 2023/04/21 23:42:34 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wall.h"

t_vars *g_vars;

int g_map[10][10] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

int32_t create_color(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void	draw_partcle(t_vars *vars)
{
	int			radius;
	int 		i;
	int 		j;
	int 		py;
	int 		px;
	uint32_t	color;

	i = -1;
	radius = 10;
	px = vars->player.x;
	py = vars->player.y;
	color = create_color(255, 255, 255, 255);
	px = px + (64 * vars->player.x) + 28;
	py = py + (64 * vars->player.y) + 28;
	for (int x = 0; x < 640; x++)
	{
		for (int y = 0; y < 640; y++)
		{
			if ((x - px) * (x - px) + (y - py) * (y - py) < radius * radius)
				mlx_put_pixel(vars->img, x ,y , color);
		}
	}
}

void	clean_partcle(t_vars *vars)
{
	int			radius;
	int 		i;
	int 		j;
	float 		py;
	float 		px;
	uint32_t	color;

	i = -1;
	radius = 10;
	px = vars->player.x;
	py = vars->player.y;
	uint32_t color_black = create_color(0, 0, 0, 255);
	px = px + (64 * vars->player.x) + 28;
	py = py + (64 * vars->player.y) + 28;

	for (int x = 0; x < 640; x++)
	{
		for (int y = 0; y < 640; y++)
		{
			if ((x - px) * (x - px) + (y - py) * (y - py) <= radius * radius)
				mlx_put_pixel(vars->img, x ,y , color_black);
		}
	}
}

// void	deprecated_draw_rays(t_vars *vars)
// {
// 	double 		angle_rad;
// 	double 		inc_x;
// 	double 		inc_y;
// 	int			radius;
// 	uint32_t	color;
// 	double 		x;
// 	double 		y;
// 	int			i;

// 	i = -1;
// 	color = create_color(0, 255, 0, 255);
// 	vars->rays_lst = (double *)malloc(sizeof(double) * 120);
// 	if(!vars->rays_lst)
// 		return ;
// 	while (++i < 120)
// 		vars->rays_lst[i] = vars->player.direction - 9.6 + (0.16 * i); // for a 60deg view (-9.6 ==> (0.16 * 120) / 2  to shift it up)
// 	i = -1;	
// 	while (++i < 120)
// 	{
// 		angle_rad = vars->rays_lst[i] * M_PI / 60;  // Convert angle to radians
// 		inc_x = cos(angle_rad);  // Calculate x increment based on angle
// 		inc_y = sin(angle_rad);  // Calculate y increment based on angle

// 		x = vars->player.x + (64 * vars->player.x) + 28;
// 		y = vars->player.y + (64 * vars->player.y) + 28;

// 		for (int j = 0; j < 220; j++)
// 		{
// 			if(y < 0 || y > 640)
// 				y = 0;
// 			mlx_put_pixel(vars->img, x, y < 0 ? 0 : y , color); //y will sigfault if < 0 || y > 640
// 			x += inc_x;
// 			y += inc_y;
// 		}
// 	}
// 	free(vars->rays_lst);
// }

void	draw_rays(t_vars *vars)
{
	int			i;
	uint32_t	color;
	double 		end_x;
	double 		end_y;
	double 		angle;
	double 		length;
	double 		start_x;
	double 		start_y;
	double 		new_end_x;
	double 		new_end_y;
	double 		angle_rad;
	
	i = -1;
	color = create_color(0, 255, 0, 255);
	vars->rays_lst = (double *)malloc(sizeof(double) * 120);
	if(!vars->rays_lst)
		return ;
	while (++i < 120)
		vars->rays_lst[i] = vars->player.direction - 9.6 + (0.16 * i); // for a 60deg view (-9.6 ==> (0.16 * 120) / 2  to shift it up)
	i = -1;	
	while (++i < 120)
	{
		angle = vars->rays_lst[i] * M_PI; // Angle in degrees
		length = 220.0; // Length of the line
		start_x = vars->player.x + (64 * vars->player.x) + 32; // Starting x-coordinate at the center of the window
		start_y =  vars->player.y + (64 * vars->player.y) + 32; // Starting y-coordinate at the center of the window
		end_x = start_x + length * cos(angle * M_PI / 180.0); // Ending x-coordinate based on angle and length
		end_y = start_y - length * sin(angle * M_PI / 180.0); // Ending y-coordinate based on angle and length
		put_line(vars->mlx, vars->win, start_x, start_y, end_x, end_y, 0xFFFFFF); // Draw the line
		find_first_intersection(vars, i);
		// if(i % 2)
		// {
		// 	new_end_x = end_x + 50 * cos(angle * M_PI / 180.0) ; // Ending x-coordinate based on angle and length
		// 	new_end_y = end_y - 50 * sin(angle * M_PI / 180.0); // Ending y-coordinate based on angle and length
		// 	put_line(vars->mlx, vars->win, end_x, end_y , new_end_x, new_end_y, 0xFFFFFF); // Draw the line
		// }
	}
	// free(vars->rays_lst);	
}

void	draw_tile(t_vars *vars, int y, int x)
{
	int	i;
	int	j;
	uint32_t color_black = create_color(0, 0, 0, 255);
	uint32_t color_white = create_color(255, 255, 255, 255);
	uint32_t color_red = create_color(255, 0, 0, 255);
	i = -1;
	while (++i < 64)
	{
		j = -1;
		while (++j < 64)
		{
			mlx_put_pixel(vars->img, (64 * y) + j, (64 * x) + i, color_black);
			if(g_map[y][x])
				mlx_put_pixel(vars->img, (64 * y) + j, (64 * x) + i, color_red);
			if(j == 63 || i == 63)
				mlx_put_pixel(vars->img, (64 * y) + j, (64 * x) + i, color_white);
		}
	}

}

void	draw_map(t_vars *vars)
{
	int	x;
	int	y;

	y = -1;
	while (++y < 10)
	{
		x = -1;
		while (++x < 10)
			draw_tile(vars, y, x);
	}

}


int key_press_handler(mlx_key_data_t keydata, void *param)
{
	t_vars	*vars;

	vars = (t_vars *)param;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_D))
	{
		draw_map(vars);
		vars->player.x += 0.1;
		draw_partcle(vars);
		draw_rays(vars);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_A))
	{
		draw_map(vars);
		vars->player.x -= 0.1;
		draw_partcle(vars);
		draw_rays(vars);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_S))
	{
		draw_map(vars);
		vars->player.y += 0.1;
		draw_partcle(vars);
		draw_rays(vars);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_W))
	{
		draw_map(vars);
		vars->player.y -= 0.1;
		draw_partcle(vars);
		draw_rays(vars);
	}
	// if (mlx_is_key_down(vars->mlx, MLX_KEY_S))
	// 	player_advance(vars->map, vars->player, -1);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
	{
		draw_map(vars);
		draw_partcle(vars);
		vars->player.direction--;
		draw_rays(vars);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
	{
		draw_map(vars);
		draw_partcle(vars);
		vars->player.direction++;
		draw_rays(vars);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE)) //free shit
		exit(0);
	return (0);
}

void	render_window(t_vars *vars)
{
	int	width;
	int	height;

	width = vars->window_info.width;
	height = vars->window_info.height;
	vars->mlx = mlx_init(width, height, "cub3D", 1);
	mlx_set_window_limit(vars->mlx,  width - 200, height - 200, width, height);
	vars->img = mlx_new_image(vars->mlx, width, height);
	draw_map(vars);
	draw_partcle(vars);
	draw_rays(vars);
	mlx_key_hook(vars->mlx, (mlx_keyfunc)key_press_handler, vars);
	mlx_image_to_window(vars->mlx, vars->img, 0, 0);
	mlx_loop(vars->mlx);
	mlx_terminate(vars->mlx);
}

int	init_vars(void)
{
	g_vars = (t_vars *)malloc(sizeof(t_vars));
	if(!g_vars)
		return (0);
	g_vars->window_info.height = 640;
	g_vars->window_info.width = 640;
	g_vars->player.direction = 0;
	g_vars->player.x = 5;
	g_vars->player.y = 4;
	g_vars->player.dx = 0;
	g_vars->player.dy = 0;
	return (1);
}


int main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	if(!init_vars())
		return (0);
	render_window(g_vars);
	return (0);
}