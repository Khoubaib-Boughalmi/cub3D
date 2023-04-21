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
}				t_map;

typedef struct s_player {
    float     x;
    float     y;
    int32_t     dx;
    int32_t     dy;

}				t_player;

typedef struct s_vars {
	mlx_t			*mlx;
	void			*win;
    mlx_image_t     *img;
	char			**map;
    t_player        player;
	t_window		window_info;
	t_map		    t_map_info;
}				t_vars;

extern t_vars *g_vars;

#define M_PI 3.14159265358979323846

# endif