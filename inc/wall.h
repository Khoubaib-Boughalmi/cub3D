# ifndef WAAL_H
# define WAAL_H

# include "./cub3d.h"

void    find_first_intersection(t_vars *vars, int ray_id);
void put_line(void *mlx_ptr, void *win_ptr, int x0, int y0, int x1, int y1, int color,int height, int width);
# endif