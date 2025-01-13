# Name: raycasting
<<<<<<< HEAD
NAME = cub3d_prueba
=======
NAME = cub3d
>>>>>>> dbc6ffb (now the hardcoded game without textures works)

# Compiler
CC = clang

# Compiler flags
FLAGS = -g -Wall -Werror -Wextra -Iinclude #-fsanitize=address

# GLFW for MLX42 linux
GLFW = -ldl -lglfw -pthread -lm 

# Source files for libft
<<<<<<< HEAD
LIBFT_PATH = ./Library/Libft
=======
LIBFT_PATH = ./Libft
>>>>>>> dbc6ffb (now the hardcoded game without textures works)

# Compiled libft
LIBFT = $(LIBFT_PATH)/libft.a

# Source files for mlx42
MLX_PATH = ./MLX42

# Compiled mlx42
MLX = $(MLX_PATH)/libmlx42.a

# Source files for mandatory
<<<<<<< HEAD
FILES = cub3d.c execute/drawing.c execute/movement.c execute/render.c execute/textures.c\
		execute/mov_forward.c execute/turn_mov.c execute/side_mov.c execute/key_a.c\
		execute/wall_texture.c
=======
FILES = execute/drawing.c cub3d.c execute/movement.c execute/render.c
>>>>>>> dbc6ffb (now the hardcoded game without textures works)

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
	@make -C $(LIBFT_PATH) all

# Build rule for mlx42
$(MLX):
	@make -C $(MLX_PATH) all

# Build rule for mandatory
all: $(NAME)

# Clean rule
clean: 
	@rm -f $(OBJS)
	@make -C $(LIBFT_PATH) clean
	@make -C $(MLX_PATH) clean

# Fclean rule
fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_PATH) fclean
	@make -C $(MLX_PATH) clean # Cambiado de fclean a clean

# Re rule
re: fclean all

.PHONY = all clean fclean re libft