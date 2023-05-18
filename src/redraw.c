/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 18:46:24 by kboughal          #+#    #+#             */
/*   Updated: 2023/05/18 18:51:56 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	redraw_shoot(t_vars *vars, char *tmp, char *str)
{
	tmp = ft_itoa(9 - g_vars->player.shoot);
	str = ft_strjoin("./src/textures/kortas/StechkinF0", tmp);
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
	str = ft_strjoin("./src/textures/kortas/StechkinR", tmp);
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

	key_press_handler(vars);
	mlx_delete_image(g_vars->mlx, g_vars->weapon_img);
	clean_window(vars);
	draw_ray(vars);
	draw_one_sprite(vars);
	if (vars->keyboard.show_map)
	{
		draw_partcle(vars);
		draw_map(vars);
	}
	if (vars->player.reload)
		redraw_reload(vars, tmp, str);
	else if (vars->player.shoot)
		redraw_shoot(vars, tmp, str);
	else
		draw_initial_gun(vars);
	draw_aim(vars);
}
