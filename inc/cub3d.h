# ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdbool.h>
# include <fcntl.h>
# include <math.h>

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/ft_printf/ft_printf.h"
# include "../libft/libft.h"

typedef struct s_window {
	int32_t     height;
	int32_t     width;
}				t_window;

typedef struct s_map {
	int32_t     height;
	int32_t     width;
	int			**map;
}				t_map;

typedef struct s_intersect {
	double      x;
	double		y;
}				t_intersect;

typedef struct s_ray {
	int	      r;
	int	      mx;
	int			my;
	int			mp;
	int			dof;
	double      rx;
	double		ry;
	double		ra;
	double		xo;
	double		yo;

}				t_ray;


typedef struct s_coord {
	int			x;
	int			y;
}				t_coord;

typedef struct s_keyboard {
	int			cursor;
	int			show_map;
}				t_keyboard;


typedef struct s_player {
	float			x;
	float       y;
	float			dx;
	float			dy;
	float			angle;
	double			prev_xpos;
	int shoot;
	int reload;
	int bullet;
	mlx_image_t * print_move;

}				t_player;

extern int g_map[31][11];
 int g_ray_ds[512];

typedef struct s_vars {
	mlx_t			*mlx;
	void			*win;
	mlx_image_t     *img;
	t_map					map;
	t_player        player;
	t_window		window_info;
	double			*rays_lst;
		mlx_image_t *wall_img;
	mlx_texture_t *wall_texture;
		mlx_image_t *weapon_img;
	mlx_texture_t *weapon_texture;
		mlx_image_t *wall_img2;
	mlx_texture_t *wall_texture2;
	mlx_texture_t *wall_texture3;
	mlx_texture_t *wall_texture4;
	mlx_texture_t *door_texture;
	mlx_texture_t *enemy_texture;
	mlx_texture_t *ammo_texture;
	mlx_image_t *ammo_img;
	t_keyboard		keyboard;
}				t_vars;

extern t_vars *g_vars;

#define PI 3.14159265358979323846
#define PI2 PI/2
#define PI3 3*PI2
#define DEG 0.0174533
void	show_gun_magazine(t_vars *vars);
void draw_wall_5(t_vars *vars, double r,double rx,double ry, double lineH);

void draw_ray(t_vars *vars);
double ft_abs(double nb);
void put_line(void *mlx_ptr, void *win_ptr, int x0, int y0, int x1, int y1, int color, int height, int width);
void draw_wall(t_vars *vars, double r,double rx,double ry, double lineH,int hororver);
float distance_to_wall(float px, float py, float wx, float wy, float angle_rad);
int32_t create_color(int32_t r, int32_t g, int32_t b, int32_t a);
void clean_window(t_vars *vars);
void draw_tile(t_vars *vars, int y, int x);
void draw_map(t_vars *vars);
void draw_partcle(t_vars *vars);
void redraw(t_vars *vars);
int key_press_handler(mlx_key_data_t keydata, void *param);
void mouse_handler(double xpos, double ypos, void *param);
void loop_func(void *data);
void render_window(t_vars *vars);
int init_vars(void);
# endif