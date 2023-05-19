/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:11:59 by aechaoub          #+#    #+#             */
/*   Updated: 2023/05/19 16:34:35 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/ft_printf/ft_printf.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_window
{
	int32_t			height;
	int32_t			width;
}					t_window;

typedef struct s_map
{
	int32_t			height;
	int32_t			width;
	int				**map;
}					t_map;

typedef struct s_rgb
{
	int				r;
	int				g;
	int				b;
}					t_rgb;

typedef struct s_line
{
	int				x0;
	int				y0;
	int				x1;
	int				y1;
	int				color;
	int				map_width;
	int				map_height;
}					t_line;

typedef struct s_map_info
{
	int				**map;
	double			x_player;
	double			y_player;
	double			angle_player;
	int				x_map_size;
	int				y_map_size;
	t_rgb			c_color;
	t_rgb			f_color;
	char			*no_texure;
	char			*so_texure;
	char			*we_texure;
	int				number_of_sprites;
	char			*ea_texure;
}					t_map_info;
typedef struct s_intersect
{
	double			x;
	double			y;
}					t_intersect;

typedef struct s_ray
{
	int				r;
	int				mx;
	int				my;
	int				mp;
	int				dof;
	double			rx;
	double			ry;
	double			ra;
	double			xo;
	double			yo;

}					t_ray;

typedef struct s_coord
{
	int				x;
	int				y;
}					t_coord;

typedef struct s_keyboard
{
	int				cursor;
	int				show_map;
}					t_keyboard;

typedef struct s_player
{
	float			x;
	float			y;
	float			dx;
	float			dy;
	float			angle;
	double			prev_xpos;
	int				shoot;
	int				reload;
	int				bullet;
	mlx_image_t		*print_move;
}					t_player;

typedef struct s_sp
{
	double			sprite_ax;
	double			sprite_ay;
	float			dx;
	float			dy;
	float			angle;
	float			angle_diff;
	float			porce_angle;
	float			v_dist;
	double			line_height;
}					t_sp;

typedef struct s_key_value
{
	int				x;
	int				y;
	int				xcheck;
	float			dxright;
	float			dyright;
	int				ycheck;
	int				factx;
	int				facty;
	float			speed;
}					t_key_value;
typedef struct s_draw_value
{
	mlx_texture_t	*imgtxet;
	int32_t			color;
	double			porcentsage;
	int				x1;
	int				k;
	int				ligne_offset;
	int				y1;
	float			y2;
	int				theline;
	float			g;
	float			rl;
	int				in;
}					t_draw_value;

typedef struct s_sprite_value
{
	mlx_texture_t	*imgtxet;
	int32_t			trans;
	int32_t			color;
	int				x1;
	float			por_h;
	float			tot_h;
	float			por_v;
	float			tot_v;
	int				ligne_offset;
	int				lol;
	int				suu;
	int				time;
	int				y1;
}					t_sprite_value;

typedef struct s_sprite
{
	float			x;
	float			y;
	char			*path;
}					t_sprite;

typedef struct s_wall
{
	double			*x_val;
	double			*y_val;
	double			*dist;
}					t_wall;

typedef struct s_bresenham
{
	int				dx;
	int				dy;
	int				sx;
	int				sy;
	int				err;
	int				err2;
}					t_bresenham;

typedef struct s_vars
{
	mlx_t			*mlx;
	void			*win;
	mlx_image_t		*img;
	t_map			map;
	t_player		player;
	t_window		window_info;
	double			*rays_lst;
	mlx_image_t		*wall_img;
	mlx_texture_t	*wall_texture;
	mlx_image_t		*weapon_img;
	mlx_texture_t	*weapon_texture;
	mlx_image_t		*wall_img2;
	mlx_texture_t	*no_wall_texture;
	mlx_texture_t	*so_wall_texture;
	mlx_texture_t	*ea_wall_texture;
	mlx_texture_t	*we_wall_texture;
	mlx_texture_t	*door_texture;
	mlx_texture_t	*enemy_texture;
	mlx_texture_t	*ammo_texture;
	mlx_image_t		*ammo_img;
	t_keyboard		keyboard;
	t_map_info		map_info;
	int				numerof_sprite;
	t_sprite		*sprites;
	int				g_ray_ds[513];
}					t_vars;

extern t_vars	*g_vars;

typedef struct s_ray_info
{
	int				ray;
	int				r;
	int				mx;
	int				my;
	int				mp;
	int				dof;
	double			rx;
	double			ry;
	double			ra;
	double			xo;
	double			yo;
	double			h_dist;
	double			h_x;
	double			h_y;
	double			v_dist;
	double			v_x;
	double			v_y;
	double			f_dist;
	float			atan;
	float			ntan;

}					t_ray_info;

# define PI 3.14159265358979323846
# define PI2 PI / 2
# define PI3 3 * PI2
# define DEG 0.0174533

int					cool(char **av, t_map_info *data);

void				show_gun_magazine(t_vars *vars);
void				draw_the_sprite(t_vars *vars, t_sp *sp, int frame,
						char *sprite_path);

void				draw_ray(t_vars *vars);
double				ft_abs(double nb);
void				put_line(t_line *line);
void				draw_wall(t_vars *vars, t_ray_info ray, double lineH,
						int hororver);
float				distance_to_wall(float px, float py, float wx, float wy);
int32_t				create_color(int32_t r, int32_t g, int32_t b, int32_t a);
void				clean_window(t_vars *vars);
void				draw_tile(t_vars *vars, int y, int x);
void				draw_map(t_vars *vars);
void				draw_partcle(t_vars *vars);
void				redraw(t_vars *vars);
int					key_press_handler_2(mlx_key_data_t keydata, void *param);
int					key_press_handler(void *param);
void				mouse_handler(double xpos, double ypos, void *param);
void				loop_func(void *data);
void				render_window(t_vars *vars);
void				free_split(char **arr);
int					init_vars(t_map_info *data);
void				ft_recalibrate(double *ra);
int					is_numerical(t_map_info *data, char *str, int selecter,
						char val);
int					check_floor_ceiling(char **floor_ceiling, t_map_info *data);
char				*ft_trim_str(char *str);
void				free_split(char **arr);
int					split_arr_len(char **arr);
int					find_in_list(char **options_list, char *needle);
int					check_all_elem(char **options_check);
int					ft_isnumber(char c);
void				textures_naming_err(char **options_check,
						char **options_list);
void				free_and_exit(char **split_line, char **options_check,
						char **options_list, char **wow);
int					check_walls(char **map, t_map_info *data);
char				**get_the_map_from_file(char *g, int fd, t_map_info *data);
void				free_g_map(int **map, int tail);
void				fillmap(char **map, t_map_info *data, int player_mara);
void				fillmap_exit(char **map, t_map_info *data);
void				for_key_w(t_vars *vars);

void				for_key_s(t_vars *vars);
void				for_key_a(t_vars *vars);
void				for_key_d(t_vars *vars);
void				for_key_right(t_vars *vars);
void				render_window(t_vars *vars);
void				my_mlx_hooks(t_vars *vars);
void				initialize_textures(void);
void				mouse_click(mouse_key_t button, action_t action,
						modifier_key_t mods, void *param);
void				draw_map(t_vars *vars);
void				draw_tile(t_vars *vars, int y, int x);
void				draw_aim(t_vars *vars);
void				draw_wal7(t_vars *vars, int r, int lineH, int32_t color);
void				redraw_shoot(t_vars *vars, char *tmp, char *str);
void				redraw_reload(t_vars *vars, char *tmp, char *str);
void				redraw(t_vars *vars);
void				clean_window(t_vars *vars);
void				draw_one_sprite(t_vars *vars);
void				draw_initial_gun(t_vars *vars);
void				show_gun_magazine(t_vars *vars);
void				for_key_w(t_vars *vars);
int32_t				collect_color(uint8_t *pixels, int index);
void				for_key_s(t_vars *vars);
void				draw_one_sprite_norm(t_vars *vars, t_sp *sp, int frame,
						int i);
int32_t				create_color(int32_t r, int32_t g, int32_t b, int32_t a);
float				distance_to_wall(float px, float py, float wx, float wy);
void				init_map_info(t_map_info *data);
int					init_vars(t_map_info *data);
void				draw_partcle(t_vars *vars);
void				loop_func(void *data);
void				mouse_handler(double xpos, double ypos, void *param);
int					key_press_handler(void *param);
void				draw_wall(t_vars *vars, t_ray_info ray, double lineH,
						int hororver);
int					draw_wall_data(t_draw_value *info, int lineH);
void				decide_vertical_textures(t_vars *vars, t_draw_value *info,
						int ry);
void				decide_horizontal_textures(t_vars *vars, t_draw_value *info,
						int rx);
void				draw_it(t_vars *vars, t_draw_value *info, int lineH);
void				check_textures(void);
int32_t				collect_color(uint8_t *pixels, int index);
void				calculate_hor_intersect(t_vars *vars, t_ray_info *ray);
void				calculate_ver_intersect(t_vars *vars, t_ray_info *ray);
void				ft_initializer(t_vars *vars, t_ray_info *ray, t_wall *wall);
void				check_for_wall(t_vars *vars, t_ray_info *ray, t_wall *wall);
void				get_shortest_intersection(t_vars *vars, t_ray_info *ray,
						int i);
void				set_initial_hwall_value(t_vars *vars, t_ray_info *ray,
						t_wall *wall);
void				set_initial_vwall_value(t_vars *vars, t_ray_info *ray,
						t_wall *wall);
#endif