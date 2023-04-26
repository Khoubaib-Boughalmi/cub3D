/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 20:46:24 by kboughal          #+#    #+#             */
/*   Updated: 2023/04/25 19:21:24 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wall.h"

t_vars *g_vars;

int g_map[8][8] = {
	{1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 0, 1, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1}
};

int32_t create_color(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

float distance_to_wall(float px, float py, float wx, float wy, float angle_rad)
{
	return (sqrt((wy - py)*(wy - py) + (wx - px)*(wx - px)));
}

void draw_wall(t_vars *vars, int r, int lineH, int line_width, int32_t color)
{
   int x1 = r * 2 + 513;
	double ligne_offset = 220 - lineH/2;
   int y1 = 220 - lineH/2;
	// Draw vertical line with specified line width
	for (int i = 0; i < 2; i++)
	{
		for (int y = y1; y <= lineH + (int)ligne_offset; y++)
		{
			mlx_put_pixel(vars->img, x1 - i, y, color);
		}
	}
}

void clean_window(t_vars *vars)
{
	for (int y = 512; y < 1024; y++)
	{
		for (int x = 0; x < 256; x++)
		{
			mlx_put_pixel(vars->img, y, x, create_color(50,150,255,255 - x));
		}
	}

	for (int y = 512; y < 1024; y++)
	{
		for (int x = 256; x < 512; x++)
		{
			mlx_put_pixel(vars->img, y, x, create_color(255,0,10, x - 255));
		}
	}
}
void draw_ray(t_vars *vars)
{
	// t_ray	ray;
	int	      r;
	int	      mx;
	int			my;
	int			mp;
	int			dof;
	double      rx;
	double		ry;
	double		ra;
	double		xo; //x offset
	double		yo; //y offset
	double		h_dist;
	double		h_x;
	double		h_y;
	double		v_dist;
	double		v_x;
	double		v_y;
	double		f_dist;

	ra = vars->player.angle - DEG * 30;
	if (ra < 0)
		ra += 2 * PI;
	if (ra > 2 * PI)
		ra -= 2 * PI;
	
	for (int i = 0; i < 256 ; i++)
	{
		h_dist = 100000;		
		h_x = vars->player.x;		
		h_y = vars->player.y;		
		/* horzontal check*/
		dof = 0;
		float aTan = -1/tan(ra);
		if (ra > PI) //facing down
		{
			ry = (((int)vars->player.y>>6)<<6)-0.0001;
			rx = (vars->player.y - ry) * aTan + vars->player.x;
			yo = -64;
			xo = -yo * aTan;
		}
		if (ra < PI) //facing up
		{
			ry = (((int)vars->player.y>>6)<<6) + 64;
			rx = (vars->player.y - ry) * aTan + vars->player.x;
			yo = 64;
			xo = -yo * aTan;
		}
		 if(ra == 0 || ra == PI)
		{
			rx = vars->player.x;
			ry = vars->player.y;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx) / 64;
			my = (int)(ry) / 64;
			if(mx >= 0 && my >= 0 && mx < 8 && my < 8 && g_map[my][mx] == 1)
			{
				h_x = rx;
				h_y = ry;
				h_dist = distance_to_wall(vars->player.x, vars->player.y, h_x, h_y, ra);
				dof = 8;
			}
			else
			{
				rx += xo;
				ry += yo;
				dof++;
			}
		}
		
		/* vertical check*/
		dof = 0;
		v_dist = 100000;		
		v_x = vars->player.x;		
		v_y = vars->player.y;		
		float nTan = -tan(ra);
		if (ra > PI2 && ra < PI3) //facing left
		{
			rx = (((int)vars->player.x>>6)<<6)-0.0001;
			ry = (vars->player.x - rx) * nTan + vars->player.y;
			xo = -64;
			yo = -xo * nTan;
		}
		if (ra < PI2 || ra > PI3) //facing right
		{
			rx = (((int)vars->player.x>>6)<<6) + 64;
			ry = (vars->player.x - rx) * nTan + vars->player.y;
			xo = 64;
			yo = -xo * nTan;
		}
		if(ra == PI2 || ra == PI3) //up or down
		{
			rx = vars->player.x;
			ry = vars->player.y;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx) / 64;
			my = (int)(ry) / 64;
			if(mx >= 0 && my >= 0 && mx < 8 && my < 8 && g_map[my][mx] == 1)
			{
				v_x = rx;
				v_y = ry;
				v_dist = distance_to_wall(vars->player.x, vars->player.y, v_x, v_y, ra);
				dof = 8;
			}
			else
			{
				rx += xo;
				ry += yo;
				dof++;
			}
		}
		if(v_dist < h_dist)
		{
			rx = v_x;
			ry = v_y;
			f_dist = v_dist;
		}
		else
		{
			rx = h_x;
			ry = h_y;
			f_dist = h_dist;
		}
		put_line(vars->mlx, vars->win, vars->player.x, vars->player.y, rx, ry, create_color(255,255,0,255), 64*8,64*8);
		double fish_eye_new_angle = vars->player.angle - ra;
		if(fish_eye_new_angle < 0)
			fish_eye_new_angle += 2*PI;
		if(fish_eye_new_angle > 2*PI)
			fish_eye_new_angle -= 2*PI;
		f_dist = f_dist * cos(fish_eye_new_angle);
		float line_height = (64 * 420)/f_dist;
		if(line_height > 440)
			line_height = 440;
		if(v_dist > h_dist)
			draw_wall(vars, i, line_height, 8, create_color(150,150,150, 256 - i ));
		else
			draw_wall(vars, i, line_height, 8, create_color(150,150,150, i));
		ra = ra + DEG / 4;
		if (ra < 0)
			ra += 2 * PI;
		if (ra > 2 * PI)
			ra -= 2 * PI;
	}
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
	for (int x = 0; x < 640; x++)
	{
		for (int y = 0; y < 640; y++)
		{
			if ((x - px) * (x - px) + (y - py) * (y - py) < radius * radius)
				mlx_put_pixel(vars->img, x ,y , color);
		}
	}
	put_line(vars->mlx, vars->win, vars->player.x, vars->player.y, vars->player.x + vars->player.dx * 10, vars->player.y + vars->player.dy * 10 , create_color(0,255,0,255), 64*8,64*8);
}

void	draw_tile(t_vars *vars, int y, int x)
{
	int	i;
	int	j;
	uint32_t color_black = create_color(0, 0, 0, 255);
	uint32_t color_white = create_color(255, 255, 255, 255);
	uint32_t color_grey = create_color(120, 120, 120, 255);
	i = -1;
	while (++i < 64)
	{
		j = -1;
		while (++j < 64)
		{
			mlx_put_pixel(vars->img, (64 * x) + i, (64 * y) + j, color_black);
			if(g_map[y][x])
				mlx_put_pixel(vars->img, (64 * x) + i, (64 * y) + j, color_grey);
			if(j == 63 || i == 63)
				mlx_put_pixel(vars->img, (64 * x) + i, (64 * y) + j, color_white);
		}
	}

}

void	draw_map(t_vars *vars)
{
	int	x;
	int	y;

	y = -1;
	while (++y < 8)
	{
		x = -1;
		while (++x < 8)
			draw_tile(vars, y, x);
	}

}

void	redraw(t_vars *vars)
{
	clean_window(vars);
	draw_map(vars);
	draw_ray(vars);
	draw_partcle(vars);

}

int key_press_handler(mlx_key_data_t keydata, void *param)
{
	t_vars	*vars;

	vars = (t_vars *)param;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
	{
		vars->player.angle += 0.1;
		if(vars->player.angle > 2*PI)
			vars->player.angle -= 2 * PI;
		vars->player.dx = 5 * cos(vars->player.angle);
		vars->player.dy = 5 * sin(vars->player.angle);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
	{
		vars->player.angle -= 0.1;
		if(vars->player.angle < 0)
			vars->player.angle += 2 * PI;
		vars->player.dx = 5 * cos(vars->player.angle);
		vars->player.dy = 5 * sin(vars->player.angle);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_W))
	{
			vars->player.x += vars->player.dx;
			vars->player.y += vars->player.dy;
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_S))
	{
			vars->player.x -= vars->player.dx;
			vars->player.y -= vars->player.dy;
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_A))
			vars->player.x -= vars->player.dx;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_D))
			vars->player.x += vars->player.dx;
	redraw(vars);
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
	clean_window(vars);
	draw_map(vars);
	draw_partcle(vars);
	draw_ray(vars);
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
	g_vars->window_info.height = 512;
	g_vars->window_info.width = 1024;
	g_vars->player.angle = 0 * (PI/180);
	g_vars->player.x = 257;
	g_vars->player.y = 257;
	g_vars->player.dx = 5 * cos(g_vars->player.angle);
	g_vars->player.dy = 5 * sin(g_vars->player.angle);
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