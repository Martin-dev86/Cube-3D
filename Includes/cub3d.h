#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdint.h>
# include <string.h>
# include <unistd.h>
# include <stdint.h>
# include "../Libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

# define MAPWIDTH 10
# define MAPHEIGHT 10
# define SCREENWIDTH 1920
# define SCREENHEIGHT 1280
# define MOVE_SPEED 0.1
# define ROT_SPEED 0.03
# define PLAYER_RADIUS 0.2

typedef struct s_textures {
    mlx_texture_t *north;
    mlx_texture_t *south;
    mlx_texture_t *west;
    mlx_texture_t *east;
} t_textures;

typedef struct s_game {
    t_textures textures;
    mlx_t *mlx;
    mlx_image_t *image;
    int screen_width;
    int screen_height;
    double player_pos_x;
    double player_pos_y;
    double player_dir_x;
    double player_dir_y;
    double plane_x;
    double plane_y;
    char **worldMap;
    int mapHeight;
} t_game;

typedef struct {
    double cameraX;
    double rayDirX;
    double rayDirY;
    int mapX;
    int mapY;
    double sideDistX;
    double sideDistY;
    int stepX;
    int stepY;
    double deltaDistX;
    double deltaDistY;
    double perpWallDist;
} t_ray;

typedef struct lines {
    int x;   
    int hit;
    int side;   
    int lineHeight;
    int drawStart;
    int drawEnd;
    uint32_t color;
} t_lines;

// Funciones
void clear_image(mlx_image_t *image, uint32_t color);
void draw_line(t_game *game, int x, int start, int end, uint32_t color);
void move_player(mlx_key_data_t keydata, void *param);
void render_floor_and_ceiling(t_game *game);
void render_walls(void *param);;
char **initialize_map(const char *mapData[], int mapHeight);
void load_walls(t_game *game);
void free_map(char **map, int mapHeight);

#endif