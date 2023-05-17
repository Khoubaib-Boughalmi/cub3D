
#include "../inc/cub3d.h"

void	draw_ray(t_vars *vars)
{
	t_ray_info	ray;
	int			i;

	i = 0;
	ray.ra = vars->player.angle - DEG * 30;
	if (ray.ra < 0)
		ray.ra += 2 * PI;
	if (ray.ra > 2 * PI)
		ray.ra -= 2 * PI;
	while (i < 512)
	{
		ray.h_dist = 100000;
		ray.h_x = vars->player.x;
		ray.h_y = vars->player.y;
		ray.dof = 0;
		ray.aTan = -1 / tan(ray.ra);
		if (ray.ra > PI)
		{
			ray.ry = (((int)vars->player.y / 64) * 64) - 0.0001;
			ray.rx = (vars->player.y - ray.ry) * ray.aTan + vars->player.x;
			ray.yo = -64;
			ray.xo = -ray.yo * ray.aTan;
		}
		if (ray.ra < PI)
		{
			ray.ry = (((int)vars->player.y / 64) * 64) + 64;
			ray.rx = (vars->player.y - ray.ry) * ray.aTan + vars->player.x;
			ray.yo = 64;
			ray.xo = -ray.yo * ray.aTan;
		}
		if (ray.ra == 0 || ray.ra == PI)
		{
			ray.rx = vars->player.x;
			ray.ry = vars->player.y;
			ray.dof = 100;
		}
		while (ray.dof < 100)
		{
			ray.mx = (int)(ray.rx) / 64;
			ray.my = (int)(ray.ry) / 64;
			if (ray.mx >= 0 && ray.my >= 0 && ray.mx < vars->map.width && ray.my < vars->map.height && vars->map.map[ray.my][ray.mx] >= 1)
			{
				ray.h_x = ray.rx;
				ray.h_y = ray.ry;
				ray.h_dist = distance_to_wall(vars->player.x, vars->player.y, ray.h_x, ray.h_y);
				break ;
			}
			else
			{
				ray.rx += ray.xo;
				ray.ry += ray.yo;
				ray.dof++;
			}
		}
		ray.dof = 0;
		ray.v_dist = 100000;
		ray.v_x = vars->player.x;
		ray.v_y = vars->player.y;
		ray.nTan = -tan(ray.ra);
		if (ray.ra > PI2 && ray.ra < PI3)
		{
			ray.rx = (((int)vars->player.x / 64) * 64) - 0.0001;
			ray.ry = (vars->player.x - ray.rx) * ray.nTan + vars->player.y;
			ray.xo = -64;
			ray.yo = -ray.xo * ray.nTan;
		}
		if (ray.ra < PI2 || ray.ra > PI3)
		{
			ray.rx = (((int)vars->player.x / 64) * 64) + 64;
			ray.ry = (vars->player.x - ray.rx) * ray.nTan + vars->player.y;
			ray.xo = 64;
			ray.yo = -ray.xo * ray.nTan;
		}
		if (ray.ra == PI2 || ray.ra == PI3)
		{
			ray.rx = vars->player.x;
			ray.ry = vars->player.y;
			ray.dof = 100;
		}
		while (ray.dof < 100)
		{
			ray.mx = (int)(ray.rx) / 64;
			ray.my = (int)(ray.ry) / 64;
			if (ray.mx >= 0 && ray.my >= 0 && ray.mx < vars->map.width && ray.my < vars->map.height && vars->map.map[ray.my][ray.mx] >= 1)
			{
				ray.v_x = ray.rx;
				ray.v_y = ray.ry;
				ray.v_dist = distance_to_wall(vars->player.x, vars->player.y, ray.v_x, ray.v_y);
				break ;
			}
			else
			{
				ray.rx += ray.xo;
				ray.ry += ray.yo;
				ray.dof++;
			}
		}
		if (ray.v_dist < ray.h_dist)
		{
			ray.rx = ray.v_x;
			ray.ry = ray.v_y;
			ray.f_dist = ray.v_dist;
		}
		else
		{
			ray.rx = ray.h_x;
			ray.ry = ray.h_y;
			ray.f_dist = ray.h_dist;
		}
		g_ray_ds[i] = ray.f_dist;
		if (vars->keyboard.show_map)
			put_line( (vars->player.x * 16) / 64, (vars->player.y * 16) / 64, (ray.rx * 16) / 64, (ray.ry * 16) / 64, create_color(255, 255, 0, 255), vars->img->width, vars->img->height);
		double fish_eye_new_angle = vars->player.angle - ray.ra;
		if (fish_eye_new_angle < 0)
			fish_eye_new_angle += 2 * PI;
		if (fish_eye_new_angle > 2 * PI)
			fish_eye_new_angle -= 2 * PI;
		ray.f_dist = ray.f_dist * cos(fish_eye_new_angle);
		double line_height = (64 * 800) / ray.f_dist;
		if (ray.v_dist > ray.h_dist)
			draw_wall(vars, i, ray.rx, ray.ry, line_height, 0);
		else
			draw_wall(vars, i, ray.rx, ray.ry, line_height, 1);
		ray.ra = ray.ra + DEG / 8;
		if (ray.ra < 0)
			ray.ra += 2 * PI;
		if (ray.ra > 2 * PI)
			ray.ra -= 2 * PI;
		i++;
	}
}
