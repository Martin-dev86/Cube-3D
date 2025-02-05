# Name: raycasting
NAME = cub3D

# Compiler
CC = clang

# Compiler flags
FLAGS = -g -Wall -Werror -Wextra -Iinclude -I$(LIBFT) #-fsanitize=address

# GLFW for MLX42 linux
GLFW = -ldl -lglfw -pthread -lm 

# Source files for libft
LIBFT_PATH = ./Library/Libft

# Compiled libft
LIBFT = $(LIBFT_PATH)/libft.a

# Source files for mlx42
MLX_PATH = ./Library/MLX42

# Compiled mlx42
MLX = $(MLX_PATH)/libmlx42.a

# Source files for mandatory
FILES = cub3d.c execute/drawing.c execute/movement.c execute/render.c execute/textures.c\
		execute/mov_forward.c execute/turn_mov.c execute/side_mov.c execute/key_a.c\
		execute/wall_texture.c execute/free_textures.c Parse/check_errors.c Parse/create_map.c\
		Parse/solid_codes.c Parse/useful_functions.c execute/player_orient.c\
		Parse/check_map_helpers.c Parse/map_checks.c Parse/free_functions.c\
		Parse/init_all.c

# Object files
OBJS = $(FILES:.c=.o)

# Compile rule
%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

# Build rule for mandatory
$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@$(CC) $(FLAGS) $(GLFW) $(OBJS) $(LIBFT) $(MLX) -o $(NAME)
	@echo "cub3d created"

# Build rule for libft
$(LIBFT):
	@make --no-print-directory -C $(LIBFT_PATH) all

# Build rule for mlx42
$(MLX):
	@make -C $(MLX_PATH) > /dev/null 2>&1 all

# Build rule for mandatory
all: $(NAME)

# Clean rule
clean: 
	@rm -f $(OBJS)
	@make -C $(LIBFT_PATH) > /dev/null 2>&1 clean
	@make -C $(MLX_PATH) > /dev/null 2>&1 clean

# Fclean rule
fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_PATH) fclean
	@make -C $(MLX_PATH) clean # Cambiado de fclean a clean

# Re rule
re: fclean all

.PHONY = all clean fclean re libft