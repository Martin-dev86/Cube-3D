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
#include "../Library/ft_printf/ft_printf.h"
# include "../MLX42/include/MLX42/MLX42.h"

//pantalla
# define MAPWIDTH 10
# define MAPHEIGHT 10
# define SCREENWIDTH 1920
# define SCREENHEIGHT 1280

//jugador
# define MOVE_SPEED 0.1
# define ROT_SPEED 0.03
# define PLAYER_RADIUS 0.2

// Colores
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define GRAY 0x808080

typedef struct s_textures
{
    mlx_texture_t *north;
    mlx_texture_t *south;
    mlx_texture_t *west;
    mlx_texture_t *east;
} t_textures;

typedef struct colors
{
    uint32_t floor;
    uint32_t ceiling;
    uint32_t player;
    uint32_t wall;
    uint32_t corridor;
} t_colors;

typedef struct s_draw_params
{
    int x;
    int draw_start;
    int draw_end;
    int tex_x;
    double tex_pos;
    double step;
    mlx_texture_t *texture;
} t_draw_params;

typedef struct s_game
{
    t_textures textures;
    mlx_t *mlx;
    mlx_image_t *image;
    t_colors colors;
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
    double camera_x;
    double ray_dir_x;
    double ray_dir_y;
    int map_x;
    int map_y;
    double side_dist_x;
    double side_dist_y;
    double delta_dist_x;
    double delta_dist_y;
    int step_x;
    int step_y;
    int side;
    int hit;
    int ray;
    double perp_wall_dist;
} t_ray;

typedef struct lines
{
    int x;   
    int hit;
    int side;   
    int lineHeight;
    int drawStart;
    int drawEnd;
    int tex_x;
    double tex_pos;
    double step;
    uint32_t color;
    mlx_texture_t *texture;
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
void error(char *str, t_game *game);


#endif