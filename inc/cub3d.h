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


typedef struct s_player {
	float			x;
	float       y;
	float			dx;
	float			dy;
	float			angle;

}				t_player;

typedef struct s_vars {
	mlx_t			*mlx;
	void			*win;
	mlx_image_t     *img;
	t_map					map;
	t_player        player;
	t_window		window_info;
	double			*rays_lst;
}				t_vars;

extern t_vars *g_vars;

// #define M_PI 3.14159265358979323846

# endif