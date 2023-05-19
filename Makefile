CC = gcc
CFLAGS = -Werror -Wextra -Wall
INC = inc
CC = gcc
SRC = src
INCLUDES = $(INC)/cub3d.h
NAME = cub3d

SRCS = $(SRC)/cub3d.c \
		$(SRC)/draw_sprite.c \
		$(SRC)/rays.c \
		$(SRC)/window.c \
		$(SRC)/utils.c \
		$(SRC)/render.c \
		$(SRC)/draw.c \
		$(SRC)/draw2.c \
		$(SRC)/draw3.c \
		$(SRC)/keys_handler.c \
		$(SRC)/keys_handler_P_2.c \
		$(SRC)/draw_wall.c \
		$(SRC)/helpers.c \
		$(SRC)/init.c \
		$(SRC)/handler.c \
		$(SRC)/keys_handler_P_3.c \
		map_utils/map_parsing.c \
		map_utils/map_parsing_part_2.c \
		map_utils/map_parsing_part_3.c \
		map_utils/get_next_line.c \
		map_utils/get_next_line_utils.c \
		map_utils/kais_said.c \
		map_utils/utils1.c \
		map_utils/utils2.c \
		map_utils/free_and_exit.c

OBJS = $(SRCS:.c=.o)
mlx_lib = MLX42/build/libmlx42.a
LIBFT = ./libft/libft.a
DEPENDENCIES = MLX42/build/libmlx42.a -framework Cocoa -framework OpenGL -framework IOKit
MLX42 = ./MLX42
INC_MLX := $(MLX42)/include
glfw=$(shell brew  --prefix glfw)

all: $(NAME)

re: fclean
	$(MAKE) all

$(LIBFT):
	make -C ./libft

$(mlx_lib):
	cmake $(MLX42) -B $(MLX42)/build
	make -C $(MLX42)/build -j4

$(NAME): $(OBJS) $(INCLUDES) $(LIBFT)
	$(CC) $(CFLAGS) ./libft/libft.a  -o $(@) $(OBJS) $(DEPENDENCIES) -lglfw -L"$(glfw)/lib"

%.o: %.c $(INCLUDES)
	$(CC) $(CFLAGS)  -I$(INC) -I$(INC_MLX) -c $(filter %.c, $<) -o $@

clean:
	rm -rf $(OBJS)
	make -C ./libft clean

fclean: clean
	rm -rf $(NAME)
	make -C ./libft fclean

.PHONY: all re clean fclean