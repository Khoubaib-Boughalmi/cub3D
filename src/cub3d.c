/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 20:46:24 by kboughal          #+#    #+#             */
/*   Updated: 2023/05/05 15:43:58 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_vars *g_vars;

int g_map[31][11] = {
	 {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	 {1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1},
	 {1, 0, 0, 1, 0, 1, 0, 1, 500, 1, 1},
	 {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	 {1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1},
	 {1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1},
	 {1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1},
	 {1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1},
	 {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	 {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	 {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	 {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	 {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	 {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	 {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	 {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	 {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	 {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	 {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	 {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	 {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	 {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	 {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	 {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	 {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	 {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	 {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	 {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	 {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
	 {1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1},
	 {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

int32_t create_color(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

float distance_to_wall(float px, float py, float wx, float wy, float angle_rad)
{
	return (sqrt((wy - py) * (wy - py) + (wx - px) * (wx - px)));
}

// void draw_wall(t_vars *vars, int r, double lineH, int32_t color)


void draw_partcle(t_vars *vars)
{
	int radius;
	int i;
	int j;
	int py;
	int px;
	uint32_t color;

	i = -1;
	radius = 3;
	px = (((vars->player.x) * 16) / 64);
	py = (((vars->player.y) * 16) / 64);
	for (int x = 0; x < 16 * vars->map.width; x++)
	{
		for (int y = 0; y < 16 * vars->map.height; y++)
		{
			if ((x - px) * (x - px) + (y - py) * (y - py) < radius * radius)
				mlx_put_pixel(vars->img, x, y, create_color(255, 255, 255, 255));
		}
	}
	put_line(vars->mlx, vars->win, px, py, px + vars->player.dx * 4, py + vars->player.dy * 4, create_color(0, 255, 0, 255), 128, 128);
}

int key_press_handler(mlx_key_data_t keydata, void *param)
{
	t_vars *vars;
	float angle;
	float dxright;
	float dyright;
	vars = (t_vars *)param;
	int x=0;
	int y=0;
	
	if (mlx_is_key_down(vars->mlx, MLX_KEY_SPACE))
	{
		int factx = (int)floor((vars->player.x) / 64);
		int facty = (int)floor((vars->player.y) / 64);
		x=factx;
		y=facty;
		int i=1;
		while(x==factx && y ==facty)
		{
			x = (int)floor((vars->player.x + (vars->player.dx * i)) / 64);
			y = (int)floor((vars->player.y + (vars->player.dy * i)) / 64);
			i++;
		}
		
		if(g_map[y][x]==500)
			g_map[y][x]=-10;
		else if(g_map[y][x]==-10)
			g_map[y][x]=500;
	}
	
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
	{
		vars->player.angle += 0.1;
		if (vars->player.angle > 2 * PI)
			vars->player.angle -= 2 * PI;
		vars->player.dx = 5 * cos(vars->player.angle);
		vars->player.dy = 5 * sin(vars->player.angle);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_T))
	{
		
		vars->player.shoot=8;
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_R))
	{
		if(!vars->player.reload && vars->player.bullet!=8)
		{
			vars->player.reload=42;
			vars->player.bullet=8;
	show_gun_magazine(vars);
			

		}
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
	{
		vars->player.angle -= 0.1;
		if (vars->player.angle < 0)
			vars->player.angle += 2 * PI;
		vars->player.dx = 5 * cos(vars->player.angle);
		vars->player.dy = 5 * sin(vars->player.angle);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_W)) /// . ila l amam
	{
		x = (int)floor((vars->player.x + (vars->player.dx * 5)) / 64);
		y = (int)floor((vars->player.y + (vars->player.dy * 5)) / 64);
		int xcheck = (int)floor((vars->player.x + (vars->player.dx )) / 64);
		int ycheck = (int)floor((vars->player.y + (vars->player.dy )) / 64);
		int factx = (int)floor((vars->player.x) / 64);
		int facty = (int)floor((vars->player.y) / 64);
		if (g_map[y][x] <= 0 && g_map[ycheck][xcheck] <= 0)
		{
			if(!(x != factx && y!=facty && g_map[y][factx] >0 && g_map[facty][x] >0))
			{
			vars->player.x += vars->player.dx;
			vars->player.y += vars->player.dy;
			}
		}
		else
		{
			if (g_map[facty][x] <= 0 && g_map[facty][xcheck] <= 0)
				vars->player.x += vars->player.dx;
			else if (g_map[y][factx] <= 0 && g_map[ycheck][factx] <= 0 )
				vars->player.y += vars->player.dy;
		}
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_S))
	{
		x = (int)floor((vars->player.x - (vars->player.dx * 2)) / 64);
		y = (int)floor((vars->player.y - (vars->player.dy * 2)) / 64);
		int factx = (int)floor((vars->player.x) / 64);
		int facty = (int)floor((vars->player.y) / 64);
		if (g_map[y][x] != 1)
		{
			vars->player.x -= vars->player.dx;
			vars->player.y -= vars->player.dy;
		}
		else
		{
			if (g_map[facty][x] != 1)
				vars->player.x -= vars->player.dx;
			if (g_map[y][factx] != 1)
				vars->player.y -= vars->player.dy;
		}
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_A))
	{
		angle = vars->player.angle - PI / 2;
		if (angle > 2 * PI)
			angle -= 2 * PI;
		if (angle < 0)
			angle += 2 * PI;

		dxright = 5 * cos(angle);
		dyright = 5 * sin(angle);
		x = (int)floor((vars->player.x + (dxright )) / 64);
		y = (int)floor((vars->player.y + (dyright )) / 64);
		int factx = (int)floor((vars->player.x) / 64);
		int facty = (int)floor((vars->player.y) / 64);
		if (g_map[y][x] != 1)
		{
			vars->player.x += dxright;
			vars->player.y += dyright;
		}
		else
		{
			if (g_map[facty][x] != 1)
				vars->player.x += dxright;
			if (g_map[y][factx] != 1)
				vars->player.y += dyright;
		}
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_D))
	{
		angle = vars->player.angle + PI / 2;
		if (angle > 2 * PI)
			angle -= 2 * PI;
		if (angle < 0)
			angle += 2 * PI;

		dxright = 5 * cos(angle);
		dyright = 5 * sin(angle);
		x = (int)floor((vars->player.x + (dxright * 2)) / 64);
		y = (int)floor((vars->player.y + (dyright * 2)) / 64);
		int factx = (int)floor((vars->player.x) / 64);
		int facty = (int)floor((vars->player.y) / 64);
		if (g_map[y][x] != 1)
		{
			vars->player.x += dxright;
			vars->player.y += dyright;
		}
		else
		{
			if (g_map[facty][x] != 1)
				vars->player.x += dxright;
			if (g_map[y][factx] != 1)
				vars->player.y += dyright;
		}
	}

	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE)) // free shit
		exit(0);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_TAB)) // free shit
	{
		if(vars->keyboard.show_map)
			vars->keyboard.show_map=0;
		else
			vars->keyboard.show_map=1;
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_F)) // free shit
	{

		mlx_set_cursor_mode(vars->mlx, vars->keyboard.cursor ? MLX_MOUSE_NORMAL : MLX_MOUSE_DISABLED);
		if(vars->keyboard.cursor)
			vars->keyboard.cursor=0;
		else
			vars->keyboard.cursor=1;
	}
	// redraw(vars);
	return (0);
}

void mouse_handler(double xpos, double ypos, void *param)
{
	t_vars *vars;
	vars = (t_vars *)param;
	
	if (xpos > vars->player.prev_xpos)
	{
		// if (xpos < 512)
		// 	xpos = 512;
		// else if (xpos > 1024)
		// 	xpos = 1024;
		vars->player.angle += 0.07;
		if (vars->player.angle > 2 * PI)
			vars->player.angle -= 2 * PI;
		vars->player.dx = 5 * cos(vars->player.angle);
		vars->player.dy = 5 * sin(vars->player.angle);
	}
	if (xpos < vars->player.prev_xpos)
	{
		// if (xpos < 512)
		// 	xpos = 512;
		// else if (xpos > 1024)
		// 	xpos = 1024;
		vars->player.angle -= 0.07;
		if (vars->player.angle < 0)
			vars->player.angle += 2 * PI;
		vars->player.dx = 5 * cos(vars->player.angle);
		vars->player.dy = 5 * sin(vars->player.angle);
	}
	vars->player.prev_xpos = xpos;
	// if(frame % 10 ==0)
	// 	redraw(vars);
	// if(frame >10000)
	// 	frame=0;
	// frame++;
}

void loop_func(void *data)
{
	t_vars *vars =(t_vars*)data;
	static int frame =0;
	if(frame % 5 ==0)
		redraw(vars);
	if(frame >10000)
		frame=0;
	frame++;
	
}


int init_vars(void)
{
	g_vars = (t_vars *)malloc(sizeof(t_vars));
	if (!g_vars)
		return (0);
	g_vars->player.shoot = 0;
	g_vars->keyboard.show_map = 0;
	g_vars->player.bullet = 8;
	g_vars->window_info.height = 1024;
	g_vars->window_info.width = 1024;
	g_vars->map.width = 11;
	g_vars->map.height = 31;
	g_vars->player.angle = 45 * (PI / 180);
	g_vars->player.prev_xpos = 0;
	g_vars->player.x = 64*2;
	g_vars->player.y = 64*2;
	g_vars->player.dx = 5 * cos(g_vars->player.angle);
	g_vars->player.dy = 5 * sin(g_vars->player.angle);
	g_vars->keyboard.cursor = 0;
	return (1);
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	if (!init_vars())
		return (0);
	render_window(g_vars);
	return (0);
}