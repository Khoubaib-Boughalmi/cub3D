# ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdbool.h>
# include <fcntl.h>

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/ft_printf/ft_printf.h"
# include "../libft/libft.h"

typedef struct s_window {
    int32_t     height;
    int32_t     width;
}				t_window;

typedef struct s_vars {
	mlx_t			*mlx;
	void			*win;
    mlx_image_t     *img;
	char			**map;
	t_window		window_info;
}				t_vars;

extern t_vars *g_vars;


# endif