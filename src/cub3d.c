/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 20:46:24 by kboughal          #+#    #+#             */
/*   Updated: 2023/04/21 01:50:10 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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

uint32_t create_color(uint8_t red, uint8_t green, uint8_t blue)
{
    return ((uint32_t)255 << 24) | ((uint32_t)red << 16) | ((uint32_t)green << 8) | (uint32_t)blue;
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
	color = create_color(255, 255, 255);
	px = px + (64 * vars->player.x) + 28;
    py = py + (64 * vars->player.y) + 28;
	
	// for (int i = 0; i < 50 * radius; i++)
    // {
    //     for (int j = 0; j < 50 * radius; j++)
    //     {
    //         if ((i - px) * (i - px) + (j - py) * (j - py) <= radius * radius)
    //         {
    //             mlx_put_pixel(vars->img, i + px, j + py, color);
    //         }
    //     }
    // }

    for (int x = 0; x < 640; x++)
    {
        for (int y = 0; y < 640; y++)
        {
			if ((x - px) * (x - px) + (y - py) * (y - py) <= radius * radius)
			{
				// mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0xFFFFFF); // Color the pixel (in this case, white)
				mlx_put_pixel(vars->img, x ,y , color);
			}
        }
    }
}


void	draw_tile(t_vars *vars, int y, int x)
{
	int	i;
	int	j;
	uint32_t color_white = create_color(255, 255, 255);
	uint32_t color_red = create_color(0, 0, 210);
	i = -1;
	while (++i < 64)
	{
		j = -1;
		while (++j < 64)
		{
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


void	key_press_handler(void *param)
{
	t_vars	*vars;

	vars = (t_vars *)param;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_W))
	{
		// vars->player.y += 0.1;
		printf("pressed\n");
		clean_partcle(vars);
		vars->player.x += 1;
		draw_partcle(vars);
		// player_advance(vars->map, vars->player, 1);
	}
	// if (mlx_is_key_down(vars->mlx, MLX_KEY_S))
	// 	player_advance(vars->map, vars->player, -1);
	// if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
	// 	rotate(vars->player, -1);
	// if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
	// 	rotate(vars->player, 1);
	// if (mlx_is_key_down(vars->mlx, MLX_KEY_A))
	// 	player_advance_lateral(vars->map, vars->player, 1);
	// if (mlx_is_key_down(vars->mlx, MLX_KEY_D))
	// 	player_advance_lateral(vars->map, vars->player, -1);
	// if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
	// {
	// 	exit(0);
	// }
	// paint(vars);
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
	mlx_loop_hook(vars->mlx, key_press_handler, vars);
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
	g_vars->player.x = 2;
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