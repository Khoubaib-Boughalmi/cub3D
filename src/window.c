/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechaoub <aechaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:43:47 by kboughal          #+#    #+#             */
/*   Updated: 2023/05/18 16:57:16 by aechaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_map(t_vars *vars)
{
	int	x;
	int	y;

	y = -1;
	while (++y < vars->map.height)
	{
		x = -1;
		while (++x < vars->map.width)
			draw_tile(vars, y, x);
	}
}

void	clean_window(t_vars *vars)
{
	int	y;
	int	x;

	y = -1;
	while (++y < 1024)
	{
		x = -1;
		while (++x < 512)
			mlx_put_pixel(vars->img, y, x, create_color(\
			vars->map_info.c_color.r, vars->map_info.c_color.g, \
			vars->map_info.c_color.b, 255 - x / 2));
	}
	y = -1;
	while (++y < 1024)
	{
		x = 511;
		while (++x < 1024)
			mlx_put_pixel(vars->img, y, x, \
			create_color(vars->map_info.f_color.r, \
			vars->map_info.f_color.g, vars->map_info.f_color.b, x / 2 - 255));
	}
}

void	draw_tile(t_vars *vars, int y, int x)
{
	int			i;
	int			j;
	uint32_t	c_w;
	uint32_t	c_g;
	uint32_t	c_b;

	i = -1;
	c_w = create_color(255, 255, 255, 255);
	c_g = create_color(160, 60, 60, 255);
	c_b = create_color(66, 6, 156, 255);
	while (++i < 16)
	{
		j = -1;
		while (++j < 16)
		{
			if (vars->map.map[y][x] == 500)
				mlx_put_pixel(vars->img, (16 * x) + i, (16 * y) + j, c_b);
			else if (vars->map.map[y][x] > 0)
				mlx_put_pixel(vars->img, (16 * x) + i, (16 * y) + j, c_g);
			if ((j == 15 || i == 15))
				mlx_put_pixel(vars->img, (16 * x) + i, (16 * y) + j, c_w);
		}
	}
}

void	draw_aim(t_vars *vars)
{
	put_line(512, 506, 512, 519, create_color(0, 255, 0, 255), \
			vars->img->width, vars->img->height);
	put_line(506, 512, 519, 512, create_color(0, 255, 0, 255), \
			vars->img->width, vars->img->height);
}

void	draw_wal7(t_vars *vars, int r, int lineH, int32_t color)
{
	int		i;
	int		y;
	int		x1;
	int		y1;
	double	ligne_offset;

	i = 0;
	x1 = r * 2 + 513;
	y1 = 220 - lineH / 2;
	ligne_offset = 220 - lineH / 2;
	while (i < 2)
	{
		y = y1;
		while (y <= lineH + (int)ligne_offset)
		{
			mlx_put_pixel(vars->img, x1 - i, y, color);
			y++;
		}
		i++;
	}
}

void	draw_one_sprite(t_vars *vars)
{

	static int	frame;
	double		sprite_ax;
	double		sprite_ay;
	float		dx;
	float		dy;
	float		angle;
	float		angle_diff ;
	float		porce_angle;
	float		v_dist;
	double		line_height;
	int			i;

	frame = 0;
	i = 0;
	while (i < vars->numerof_sprite)
	{
		sprite_ax=vars->sprites[i].x;
		sprite_ay=vars->sprites[i].y;
		dx = sprite_ax- vars->player.x  ;
		dy = sprite_ay -vars->player.y ;
		angle = atan2(dy, dx);
		if(angle >  vars->player.angle+PI)
				angle -= 2 * PI;
		if(angle <  vars->player.angle-PI)
				angle += 2 * PI;
		angle_diff = angle - vars->player.angle;
		porce_angle =angle_diff*180/PI;
		if(angle_diff*180/PI<=50 &&angle_diff*180/PI>=-50 )
		{
			porce_angle=(porce_angle+30)/60*512;
			v_dist = distance_to_wall(vars->player.x, vars->player.y, sprite_ax, sprite_ay);
			line_height = (64 * 600) / v_dist;
			draw_the_sprite(vars,(int)porce_angle,v_dist,line_height,frame,vars->sprites[i].path);
		}
		i++;
	}
		frame++;
	if(frame ==8)
		frame =0;
}

void  redraw(t_vars *vars)
{
	char *str;
	char *tmp;
	key_press_handler(vars);
	mlx_delete_image(g_vars->mlx,g_vars->weapon_img);
	clean_window(vars);
	draw_ray(vars);
	draw_one_sprite(vars);
	if(vars->keyboard.show_map)
	{
		draw_partcle(vars);
		draw_map(vars);
	}

	if(vars->player.reload)
	{
		tmp=ft_itoa(43-g_vars->player.reload);
		str=ft_strjoin("./src/textures/kortas/StechkinR",tmp);
		free(tmp);
		tmp=str;
		str=ft_strjoin(str,".png");
		free(tmp);
		g_vars->weapon_texture  = mlx_load_png(str);
		g_vars->weapon_img = mlx_texture_to_image(g_vars->mlx, g_vars->weapon_texture);
		mlx_image_to_window(vars->mlx,vars->weapon_img,50,257);
		mlx_delete_texture(g_vars->weapon_texture);
		free(str);
		g_vars->player.reload--;
		vars->player.shoot = 0;
	}
	else if(vars->player.shoot)
	{
		tmp=ft_itoa(9-g_vars->player.shoot);
		str=ft_strjoin("./src/textures/kortas/StechkinF0",tmp);
		free(tmp);
		tmp =str;
		str=ft_strjoin(str,".png");
		g_vars->weapon_texture  = mlx_load_png(str);
		g_vars->weapon_img = mlx_texture_to_image(g_vars->mlx, g_vars->weapon_texture);
		mlx_image_to_window(vars->mlx,vars->weapon_img,50,257);
		mlx_delete_texture(g_vars->weapon_texture);
		free(str);
		free(tmp);
		g_vars->player.shoot--;
	}
	else
	{
	g_vars->weapon_texture  = mlx_load_png("./src/textures/kortas/StechkinEx01.png");
	g_vars->weapon_img = mlx_texture_to_image(g_vars->mlx, g_vars->weapon_texture);
	mlx_image_to_window(vars->mlx,vars->weapon_img,50,257);
	mlx_delete_texture(g_vars->weapon_texture);
	}
    draw_aim(vars);
}


void	show_gun_magazine(t_vars *vars)
{
	char *tmp=ft_itoa(vars->player.bullet);
	char *str=ft_strjoin(": ",tmp);
	mlx_image_to_window(vars->mlx,vars->ammo_img,840,45);
	mlx_delete_image(vars->mlx,vars->player.print_move);
	vars->player.print_move=mlx_put_string(vars->mlx,str,880,52);
	free(str);
	free(tmp);
}


void mouse_click(mouse_key_t button, action_t action, modifier_key_t mods, void *param)
{
	t_vars *vars;
	vars = (t_vars *)param;
	(void)mods;

	if(button==0 && action == 1 && vars->player.bullet && !vars->player.reload)
	{
		vars->player.bullet--;
		vars->player.shoot=8;
		show_gun_magazine(vars);

	}
	else if(button==0 && action == 1 && !vars->player.bullet && !vars->player.reload)
	{
		vars->player.bullet=8;
		vars->player.reload=42;
		show_gun_magazine(vars);
	}


}

void render_window(t_vars *vars)
{
	int width;
	int height;

	width = vars->window_info.width;
	height = vars->window_info.height;
	vars->mlx = mlx_init(width, height, "cub3D", 1);
	if (!vars->mlx)
	{
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
		exit(1);
	}
	g_vars->player.reload=0;
	g_vars->SO_wall_texture  = mlx_load_png(g_vars->map_info.SO_texure);
	g_vars->EA_wall_texture  = mlx_load_png(g_vars->map_info.WE_texure);
	g_vars->WE_wall_texture  = mlx_load_png(g_vars->map_info.EA_texure);
	g_vars->NO_wall_texture_texture  = mlx_load_png(g_vars->map_info.NO_texure);
	free(g_vars->map_info.NO_texure);
	free(g_vars->map_info.SO_texure);
	free(g_vars->map_info.WE_texure);
	free(g_vars->map_info.EA_texure);
	g_vars->door_texture  = mlx_load_png("./src/textures/doorx.png");
	g_vars->enemy_texture  = mlx_load_png("./src/textures/enemy1.png");
	g_vars->ammo_texture  = mlx_load_png("./src/textures/bullet.png");
	g_vars->ammo_img = mlx_texture_to_image(g_vars->mlx, g_vars->ammo_texture);
	mlx_set_window_limit(vars->mlx, width - 200, height - 200, width, height);
	vars->img = mlx_new_image(vars->mlx, width, height);
	redraw(vars);
	mlx_set_cursor_mode(vars->mlx, vars->keyboard.cursor ? MLX_MOUSE_NORMAL : MLX_MOUSE_DISABLED);
	mlx_key_hook(vars->mlx, (mlx_keyfunc)key_press_handler_2, vars);
	mlx_cursor_hook(vars->mlx, (mlx_cursorfunc)mouse_handler, vars);
	mlx_mouse_hook(vars->mlx, (mlx_mousefunc)mouse_click, vars);
	mlx_image_to_window(vars->mlx, vars->img, 0, 0);
	mlx_loop_hook(vars->mlx,&loop_func,vars);
	show_gun_magazine(vars);
	mlx_loop(vars->mlx);
	mlx_terminate(vars->mlx);
}