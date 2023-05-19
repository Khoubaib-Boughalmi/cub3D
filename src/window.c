/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechaoub <aechaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:43:47 by kboughal          #+#    #+#             */
/*   Updated: 2023/05/18 22:05:04 by aechaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	clean_window(t_vars *vars)
{
	int	y;
	int	x;

	y = 0;
	while (y < 1024)
	{
		x = -1;
		while (++x < 512)
			mlx_put_pixel(vars->img, y, x, \
			create_color(vars->map_info.c_color.r, \
			vars->map_info.c_color.g, vars->map_info.c_color.b, 255 - x / 2));
		y++;
	}
	y = 0;
	while (y < 1024)
	{
		x = 511;
		while (++x < 1024)
			mlx_put_pixel(vars->img, y, x, \
			create_color(vars->map_info.f_color.r, \
			vars->map_info.f_color.g, vars->map_info.f_color.b, x / 2 - 255));
		y++;
	}
}

void	draw_one_sprite(t_vars *vars)
{
	static int	frame = 0;
	t_sp		sp;
	int			i;

	i = 0;
	while (i < vars->numerof_sprite)
	{
		sp.sprite_ax = vars->sprites[i].x;
		sp.sprite_ay = vars->sprites[i].y;
		sp.dx = sp.sprite_ax - vars->player.x ;
		sp.dy = sp.sprite_ay - vars->player.y;
		sp.angle = atan2(sp.dy, sp.dx);
		if (sp.angle > vars->player.angle + PI)
				sp.angle -= 2 * PI;
		if (sp.angle < vars->player.angle - PI)
				sp.angle += 2 * PI;
		sp.angle_diff = sp.angle - vars->player.angle;
		sp.porce_angle = sp.angle_diff * 180 / PI;
		if (sp.angle_diff * 180 / PI <= 50 && sp.angle_diff * 180 / PI >= -50)
			draw_one_sprite_norm(vars, &sp, frame, i);
		i++;
	}
	frame++;
	if (frame == 8)
		frame = 0;
}

void	draw_initial_gun(t_vars *vars)
{
	g_vars->weapon_texture = \
	mlx_load_png("./src/textures/kortas/StechkinEx01.png");
	if(!g_vars->weapon_texture)
	{
		printf("Error image \n");
		exit(0);
	}
	g_vars->weapon_img = mlx_texture_to_image(g_vars->mlx, \
	g_vars->weapon_texture);
	mlx_image_to_window(vars->mlx, vars->weapon_img, 50, 257);
	mlx_delete_texture(g_vars->weapon_texture);
}

void	show_gun_magazine(t_vars *vars)
{
	char	*tmp;
	char	*str;

	tmp = ft_itoa(vars->player.bullet);
	str = ft_strjoin(": ", tmp);
	mlx_image_to_window(vars->mlx, vars->ammo_img, 840, 45);
	mlx_delete_image(vars->mlx, vars->player.print_move);
	vars->player.print_move = mlx_put_string(vars->mlx, str, 880, 52);
	free(str);
	free(tmp);
}
