CC = gcc
CFLAGS = #-Wall -Werror -Wextra -g
INC = inc
SRC = src
INCLUDES = $(INC)/cub3d.h


SRCS = $(SRC)/cub3d.c \

OBJS = $(SRCS:.c=.o)
NAME = cub3d
VALGRIND = val
mlx_lib = MLX42/build/libmlx42.a
LIBFT = ./libft/libft.a
#------------------------ MLX_DEPENDENCIES --------------------------
DEPENDENCIES_LINUX = $(mlx_lib) -ldl -lglfw -pthread -lm
DEPENDENCIES_MAC = MLX42/build/libmlx42.a -framework Cocoa -framework OpenGL -framework IOKit
MLX42 = ./MLX42
INC_MLX := $(MLX42)/include

#Variables to make an executable in differents OS
LINUX = Linux
MAC = Darwin

#------------------------- Recipes -----------------------

all: $(NAME)

re: fclean
	$(MAKE) all

$(LIBFT):
	make -C ./libft

$(mlx_lib):
	cmake $(MLX42) -B $(MLX42)/build
	make -C $(MLX42)/build -j4

ifeq ($(shell uname -s), $(LINUX))

%.o: %.c $(INCLUDES)  $(LIBFT)
	$(CC) $(CFLAGS) -g -I$(INC) -I$(INC_MLX) -I./libft -c $(filter %.c, $<) -o $@

$(NAME): $(OBJS) $(INCLUDES) $(mlx_lib)
	$(CC) $(FLAGS) -g -o $@ $(OBJS) ./libft/libft.a $(DEPENDENCIES_LINUX)
else ifeq ($(shell uname -s), $(MAC))

$(NAME): $(OBJS) $(INCLUDES) $(mlx_lib) $(LIBFT)
	$(CC) $(CFLAGS) ./libft/libft.a -g -o $(@) $(OBJS) $(DEPENDENCIES_MAC) -lglfw -L"/Users/${USER}/.brew/opt/glfw/lib/"

%.o: %.c $(INCLUDES) $(mlx_lib)
	$(CC) $(CFLAGS) -g -I$(INC) -I$(INC_MLX) -c $(filter %.c, $<) -o $@

endif

clean:
	rm -rf $(MLX42)/build
	rm -rf $(OBJS)
	make -C ./libft clean

fclean: clean
	rm -rf $(NAME)
	make -C ./libft fclean

$(VALGRIND): $(NAME)
	valgrind --leak-check=full ./$(NAME)
	rm -rf $(NAME).dSYM
.PHONY: all re clean fclean val