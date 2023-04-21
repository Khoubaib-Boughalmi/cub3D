#include "../inc/cub3d.h"

//find slope of the ray
//calculate point_A.y
//calculate point_A.x
//find X_A
//keep adding X_A to find the horizental intersection with the wall

void    find_first_intersection(t_vars *vars)
{
    t_intersect point_A;
    int         slope;
    double 		angle_rad;
	double 		inc_x;
	double 		inc_y;
    int         i;

    i = -1;
    angle_rad = vars->rays_lst[0] * M_PI / 60;  // Convert angle to radians
    inc_x = cos(angle_rad);  // Calculate x increment based on angle
    inc_y = sin(angle_rad);  // Calculate y increment based on angle
    // slope = vars->player.
    for (int j = 0; j < 50; j++)
    {
        mlx_put_pixel(vars->img, inc_x + j, inc_y + 100 , 0x00FF00FF); //y will sigfault if < 0 || y > 640
        // inc_x += inc_x;
        // inc_y += inc_y;
    }
}