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

    slop = (vars->rays_lst[ray_id] * M_PI) * (M_PI / 180) ;
    // A.y = rounded_down(Py/64) * (64) - 1;
    //  A.y = rounded_down(Py/64) * (64) + 64;
    // printf("slop[]: %f\n", vars->rays_lst[119] * M_PI);
    if(tan(slop) > 0)
    {
        point_A.y = floor((vars->player.y * 64 + 32)/64) * (64) - 1;
        // printf("slop up\n");
    }
    else
    {
        point_A.y = floor((vars->player.y * 64 + 32)/64) * (64) + 64;
        // printf("slop down\n");
    }
    // >>> 96+(224-math.floor(224/64)*64 - 1)*math.tan(60)
    // A.x = Px + (Py-A.y)/tan(ALPHA);
    point_A.x = (vars->player.x * 64 + 32) + (point_A.y - floor(point_A.y/64)*64 - 1)*slop;
    // >>> 96+(191-math.floor(191/64)*64 -1)*math.tan(60)
    printf("xx: %f %f\n", point_A.x, point_A.y);
    coord_A.x = point_A.x / 64 ;
    coord_A.y = point_A.y / 64 ;
    // if(g_map_dup[coord_A.x][coord_A.y] == 1)
    //     printf("WALL %d coor %d %d\n", ray_id, coord_A.x, coord_A.y);
    // else
    //     printf("NO WALL %d coor %d %d\n", ray_id, coord_A.x, coord_A.y);
}