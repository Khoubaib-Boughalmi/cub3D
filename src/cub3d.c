/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 20:46:24 by kboughal          #+#    #+#             */
/*   Updated: 2023/05/18 21:07:51 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"


int32_t create_color(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

float distance_to_wall(float px, float py, float wx, float wy)
{
	return (sqrt((wy - py) * (wy - py) + (wx - px) * (wx - px)));
}

// void draw_wall(t_vars *vars, int r, double lineH, int32_t color)


void draw_partcle(t_vars *vars)
{
	int radius;
	int i;
	int py;
	int px;

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
	// put_line( px, py, px + vars->player.dx * 4, py + vars->player.dy * 4, create_color(0, 255, 0, 255), 128, 128);
}




int key_press_handler( void *param)
{
	t_vars *vars;
	vars = (t_vars *)param;
	
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
		for_key_right(vars);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
	{
		vars->player.angle -= 0.1;
		if (vars->player.angle < 0)
			vars->player.angle += 2 * PI;
		vars->player.dx = 5 * cos(vars->player.angle);
		vars->player.dy = 5 * sin(vars->player.angle);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_W))
		for_key_w(vars);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_S))
		for_key_s(vars);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_A))
		for_key_a(vars);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_D))
		for_key_d(vars);
	return (0);
}


void mouse_handler(double xpos, double ypos, void *param)
{
	t_vars *vars;
	vars = (t_vars *)param;
	(void)ypos;
	
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
	// printf("%d\n",frame);
	if(frame % 5 ==0)
		redraw(vars);
	if(frame >10000)
		frame=0;
	frame++;
	
}

void	init_map_info(t_map_info *data)
{
	g_vars->map_info.c_color.r = data->c_color.r;
	g_vars->map_info.c_color.g = data->c_color.g;
	g_vars->map_info.c_color.b = data->c_color.b;
	g_vars->map_info.f_color.b = data->f_color.b;
	g_vars->map_info.f_color.r = data->f_color.r;
	g_vars->map_info.f_color.g = data->f_color.g;
	g_vars->map_info.NO_texure = data->NO_texure;
	g_vars->map_info.SO_texure = data->SO_texure;
	g_vars->map_info.WE_texure = data->WE_texure;
	g_vars->map_info.EA_texure = data->EA_texure;
}

int init_vars(t_map_info *data)
{
	g_vars = (t_vars *)malloc(sizeof(t_vars));
	if (!g_vars)
		return (0);
	g_vars->player.shoot = 0;
	g_vars->keyboard.show_map = 0;
	g_vars->player.bullet = 8;
	g_vars->window_info.height = 1024;
	g_vars->window_info.width = 1024;
	g_vars->map.map=data->map;
	g_vars->map.width = data->x_map_size;
	g_vars->map.height = data->y_map_size;
	g_vars->player.angle = data->angle_player * (PI / 180);
	g_vars->player.prev_xpos = 0;
	g_vars->player.x = data->x_player+32;
	g_vars->player.y = data->y_player+32;
	g_vars->player.dx = 5 * cos(g_vars->player.angle);
	g_vars->player.dy = 5 * sin(g_vars->player.angle);
	g_vars->keyboard.cursor = 0;
	init_map_info(data);
	return (1);
}



void randomize_the_sprites(t_map_info *data)
{
	int i =0;
	int sprite =0;
	int j =0;
	g_vars->numerof_sprite=data->number_of_sprites;
	g_vars->sprites=malloc(sizeof(t_sprite)*g_vars->numerof_sprite);
	// for (int i=0; i<g_vars->numerof_sprite ; i++)
	// {
	// 	g_vars->sprites[i].x=64*i+200;
	// 	g_vars->sprites[i].y=64*i+640;
	// 	if(i%2==0)
	// 		g_vars->sprites[i].path=ft_strdup("./src/textures/sprites/");
	// 	else
	// 		g_vars->sprites[i].path=ft_strdup("./src/textures/sprites/g");
	// }
    // printf("----------------------\n\n\n\n\n%d\n",data->number_of_sprites);

	while(i < data->y_map_size)
    {
		j=0;
        while( j < data->x_map_size)
		{
			if(data->map[i][j]==-2 && sprite < 15)
			{
				g_vars->sprites[sprite].x=64*j+32;
				g_vars->sprites[sprite].y=64*i+32;
				if(i%2==0)
					g_vars->sprites[sprite].path=ft_strdup("./src/textures/sprites/");
				else
					g_vars->sprites[sprite].path=ft_strdup("./src/textures/sprites/g");
				data->map[i][j]=0;
				sprite++;
			}
			j++;
		}
        // printf("},\n{");

		i++;
    }
}



int main(int argc, char **argv)
{
	// (void)argc;
	// (void)argv;
	if(argc!=2)
	{
		printf("map required\n");
		exit (1);
	}

	t_map_info data;
    cool(argv,&data);

	if (!init_vars(&data))
		return (0);
	randomize_the_sprites(&data);
	render_window(g_vars);
	return (0);
}