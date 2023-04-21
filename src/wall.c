#include "../inc/cub3d.h"
#include "../inc/utils.h"


int g_map_dup[10][10] = {
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

//find slope of the ray
//calculate point_A.y
//calculate point_A.x
//find X_A
//keep adding X_A to find the horizental intersection with the wall


void    find_first_intersection(t_vars *vars, int ray_id)
{
    double      slop;
    t_intersect point_A;
    t_coord     coord_A;

    slop = vars->rays_lst[119] * (M_PI/180);
    // A.y = rounded_down(Py/64) * (64) - 1;
    //  A.y = rounded_down(Py/64) * (64) + 64;
    if(slop > 0)
    {
        point_A.y = floor((vars->player.y * 64 + 32)/64) * (64) - 1;
        printf("slop up\n");
    }
    else
    {
        point_A.y = floor((vars->player.y * 64 + 32)/64) * (64) + 64;
        printf("slop down\n");
    }

    // A.x = Px + (Py-A.y)/tan(ALPHA);
    point_A.x = (vars->player.x * 64 + 32) + ((vars->player.y * 64 + 32) - point_A.y)/tan(30);
    coord_A.x = point_A.x / 64;
    coord_A.y = point_A.y / 64;
    if(g_map_dup[coord_A.x][coord_A.y] == 1)
        printf("WALL %d\n", ray_id);
    else
        printf("NO WALL %d\n", ray_id);
}