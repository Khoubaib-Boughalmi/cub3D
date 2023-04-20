/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 20:46:24 by kboughal          #+#    #+#             */
/*   Updated: 2023/04/20 21:27:26 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_vars *g_vars;
//initiate variables and populate structs
void	render_window(t_vars *vars)
{
	int	width;
	int	height;

	width = vars->window_info.width;
	height = vars->window_info.height;
	vars->mlx = mlx_init(height, width, "cub3D", 1);
	mlx_set_window_limit(vars->mlx, height - 100, width - 100, height, width);
	vars->img = mlx_new_image(vars->mlx, height, width);
	mlx_image_to_window(vars->mlx, vars->img, 0, 0);
	mlx_loop(vars->mlx);
	mlx_terminate(vars->mlx);
}

int	init_vars(void)
{
	g_vars = (t_vars *)malloc(sizeof(t_vars));
	if(g_vars)
		return (0);
	g_vars->window_info.height = 200;
	g_vars->window_info.width = 320;
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