
#include "../inc/cub3d.h"

void draw_ray(t_vars *vars)
{
	int		r;
	int		mx;
	int		my;
	int		mp;
	int		dof;
	double	rx;
	double	ry;
	double	ra;
	double	xo;
	double	yo;
	double	h_dist;
	double	h_x;
	double	h_y;
	double	v_dist;
	double	v_x;
	double	v_y;
	double	f_dist;
	float	aTan;
	float	nTan;

	ra = vars->player.angle - DEG * 30;
	if (ra < 0)
		ra += 2 * PI;
	if (ra > 2 * PI)
		ra -= 2 * PI;

	for (int i = 0; i < 512; i++)
	{
		h_dist = 100000;
		h_x = vars->player.x;
		h_y = vars->player.y;
		dof = 0;
		aTan = -1 / tan(ra);
		if (ra > PI)
		{
			ry = (((int)vars->player.y / 64) * 64) - 0.0001;
			rx = (vars->player.y - ry) * aTan + vars->player.x;
			yo = -64;
			xo = -yo * aTan;
		}
		if (ra < PI)
		{
			ry = (((int)vars->player.y / 64) * 64) + 64;
			rx = (vars->player.y - ry) * aTan + vars->player.x;
			yo = 64;
			xo = -yo * aTan;
		}
		if (ra == 0 || ra == PI)
		{
			rx = vars->player.x;
			ry = vars->player.y;
			dof = 100;
		}
		while (dof < 100)
		{
			mx = (int)(rx) / 64;
			my = (int)(ry) / 64;
			if (mx >= 0 && my >= 0 && mx < vars->map.width && my < vars->map.height && vars->map.map[my][mx] >= 1)
			{
				h_x = rx;
				h_y = ry;
				h_dist = distance_to_wall(vars->player.x, vars->player.y, h_x, h_y, ra);
				break;
			}
			else
			{
				rx += xo;
				ry += yo;
				dof++;
			}
		}
		dof = 0;
		v_dist = 100000;
		v_x = vars->player.x;
		v_y = vars->player.y;
		nTan = -tan(ra);
		if (ra > PI2 && ra < PI3)
		{
			rx = (((int)vars->player.x / 64) * 64) - 0.0001;
			ry = (vars->player.x - rx) * nTan + vars->player.y;
			xo = -64;
			yo = -xo * nTan;
		}
		if (ra < PI2 || ra > PI3)
		{
			rx = (((int)vars->player.x / 64) * 64) + 64;
			ry = (vars->player.x - rx) * nTan + vars->player.y;
			xo = 64;
			yo = -xo * nTan;
		}
		if (ra == PI2 || ra == PI3)
		{
			rx = vars->player.x;
			ry = vars->player.y;
			dof = 100;
		}
		while (dof < 100)
		{
			mx = (int)(rx) / 64;
			my = (int)(ry) / 64;
			if (mx >= 0 && my >= 0 && mx < vars->map.width && my < vars->map.height && vars->map.map[my][mx] >= 1)
			{
				v_x = rx;
				v_y = ry;
				v_dist = distance_to_wall(vars->player.x, vars->player.y, v_x, v_y, ra);
				break;
			}
			else
			{
				rx += xo;
				ry += yo;
				dof++;
			}
		}
		if (v_dist < h_dist)
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
		g_ray_ds[i]=f_dist;
		if(vars->keyboard.show_map)
			put_line(vars->mlx, vars->win, (vars->player.x * 16) / 64, (vars->player.y * 16) / 64, (rx * 16) / 64, (ry * 16) / 64, create_color(255, 255, 0, 255), vars->img->width, vars->img->height);
		double fish_eye_new_angle = vars->player.angle - ra;
		if (fish_eye_new_angle < 0)
			fish_eye_new_angle += 2 * PI;
		if (fish_eye_new_angle > 2 * PI)
			fish_eye_new_angle -= 2 * PI;
		f_dist = f_dist * cos(fish_eye_new_angle);
		double line_height = (64 * 800) / f_dist;
		if (v_dist > h_dist)
			draw_wall(vars, i, rx,ry , line_height, 0);
		else
			draw_wall(vars, i, rx,ry ,line_height,1);
		ra = ra + DEG / 8;
		if (ra < 0)
			ra += 2 * PI;
		if (ra > 2 * PI)
			ra -= 2 * PI;
	}
}
