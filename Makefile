CC = gcc
CFLAGS =  -Werror -Wextra -Wall #-fsanitize=address -g
INC = inc
CFLAGS = -Werror -Wextra -Wextra -fsanitize=address -g 
CC = gcc
SRC = src
INCLUDES = $(INC)/cub3d.h


SRCS = $(SRC)/cub3d.c \
		$(SRC)/wall.c \
		$(SRC)/rays.c \
		$(SRC)/window.c \
		$(SRC)/utils.c \
		map_utils/map_parsing.c \
		map_utils/get_next_line.c \
		map_utils/get_next_line_utils.c \
		map_utils/kais_said.c \
		map_utils/utils1.c \
		map_utils/utils2.c \
		map_utils/free_and_exit.c

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
glfw=$(shell brew  --prefix glfw)

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

$(NAME): $(OBJS) $(INCLUDES)
	$(CC) $(FLAGS) -g -o $@ $(OBJS) ./libft/libft.a $(DEPENDENCIES_LINUX)
else ifeq ($(shell uname -s), $(MAC))

$(NAME): $(OBJS) $(INCLUDES) $(LIBFT)
	$(CC) $(CFLAGS) ./libft/libft.a -g -o $(@) $(OBJS) $(DEPENDENCIES_MAC) -lglfw -L"$(glfw)/lib"

%.o: %.c $(INCLUDES)
	$(CC) $(CFLAGS) -g -I$(INC) -I$(INC_MLX) -c $(filter %.c, $<) -o $@

endif

clean:
	rm -rf $(OBJS)
	make -C ./libft clean

fclean: clean
	rm -rf $(NAME)
	make -C ./libft fclean

$(VALGRIND): $(NAME)
	valgrind --leak-check=full ./$(NAME)
	rm -rf $(NAME).dSYM
.PHONY: all re clean fclean val