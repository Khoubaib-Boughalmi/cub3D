/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechaoub <aechaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 18:46:24 by kboughal          #+#    #+#             */
/*   Updated: 2023/05/19 19:00:19 by aechaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	redraw_shoot(t_vars *vars, char *tmp, char *str)
{
	tmp = ft_itoa(9 - g_vars->player.shoot);
	str = ft_strjoin("./textures/kortas/StechkinF0", tmp);
	free(tmp);
	tmp = str;
	str = ft_strjoin(str, ".png");
	g_vars->weapon_texture = mlx_load_png(str);
	g_vars->weapon_img = mlx_texture_to_image(g_vars->mlx, \
	g_vars->weapon_texture);
	mlx_image_to_window(vars->mlx, vars->weapon_img, 50, 257);
	mlx_delete_texture(g_vars->weapon_texture);
	free(str);
	free(tmp);
	g_vars->player.shoot--;
}

void	redraw_reload(t_vars *vars, char *tmp, char *str)
{
	tmp = ft_itoa(43 - g_vars->player.reload);
	str = ft_strjoin("./textures/kortas/StechkinR", tmp);
	free(tmp);
	tmp = str;
	str = ft_strjoin(str, ".png");
	free(tmp);
	g_vars->weapon_texture = mlx_load_png(str);
	g_vars->weapon_img = mlx_texture_to_image(g_vars->mlx, \
	g_vars->weapon_texture);
	mlx_image_to_window(vars->mlx, vars->weapon_img, 50, 257);
	mlx_delete_texture(g_vars->weapon_texture);
	free(str);
	g_vars->player.reload--;
	vars->player.shoot = 0;
}

void	redraw(t_vars *vars)
{
	char	*str;
	char	*tmp;

	tmp = NULL;
	str = NULL;
	key_press_handler(vars);
	mlx_delete_image(g_vars->mlx, g_vars->weapon_img);
	clean_window(vars);
	draw_ray(vars);
}

void	draw_partcle(t_vars *vars)
{
	t_line	line;
	int		radius;
	int		i;
	int		x;
	int		y;

	x = 0;
	i = -1;
	radius = 3;
	line.x0 = (vars->player.x * 16) / 64;
	line.y0 = (vars->player.y * 16) / 64;
	while (x < 16 * vars->map.width)
	{
		y = 0;
		while (y < 16 * vars->map.height)
		{
			if ((x - line.x0) * (x - line.x0) + (y - line.y0) \
				* (y - line.y0) < radius * radius)
				mlx_put_pixel(vars->img, x, y, \
				create_color(255, 255, 255, 255));
			y++;
		}
		x++;
	}
}

void	draw_wall(t_vars *vars, t_ray_info	ray, double lineH, int hororver)
{
	t_draw_value	info;

	if (hororver == 1)
		info.porcentsage = ray.ry / 64;
	if (hororver == 0)
		info.porcentsage = ray.rx / 64;
	info.porcentsage -= (int)info.porcentsage;
	info.x1 = ray.ray * 2 + 2;
	lineH = draw_wall_data(&info, lineH);
	if (vars->map.map[(int)floor(ray.ry / 64)][(int)floor(ray.rx / 64)] == 500)
		info.imgtxet = vars->door_texture;
	else if (hororver == 0)
		decide_vertical_textures(vars, &info, ray.ry);
	else if (hororver == 1)
		decide_horizontal_textures(vars, &info, ray.rx);
	info.theline = (int)(info.porcentsage * 512);
	info.theline *= 4;
	info.g = (float)512 / info.k;
	info.rl = 0;
	info.in = 0;
	draw_it(vars, &info, lineH);
}
