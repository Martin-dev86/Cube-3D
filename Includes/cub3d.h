/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:22:18 by jeandrad          #+#    #+#             */
/*   Updated: 2025/02/01 17:58:20 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../Library/Libft/libft.h"
# include "../Library/MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <memory.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

// Constants values for the game
// Width and height of the map
// Width and height of the screen
// Speed of movement of the player
// Speed of the rotation of the player
// Radius of the player for improved collisions
# define MAPWIDTH 10
# define MAPHEIGHT 10
# define SCREENWIDTH 1920
# define SCREENHEIGHT 1280
# define MOVE_SPEED 0.1
# define ROT_SPEED 0.03
# define PLAYER_RADIUS 0.2

# define WALL '1'
# define FLOOR '0'

// For the wall textures
typedef struct s_texture
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*east;
}					t_textures;

// For the path or the map elements
typedef struct s_element
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	char			*floor;
	char			*ceiling;
}					t_element;

// Main structure for the game
// POSX and POSY are the position of the player
// DIRX and DIRY are the direction of the camera
// PLANEX and PLANEY are the plane of the camera
typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	t_textures		textures;
	mlx_texture_t	*texture;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	char			**map;
	char			**world_map;
	int				map_width;
	int				map_height;
	char			initial_orientation;
	uint32_t		color;
	uint32_t		floor;
	uint32_t		ceiling;
	int				file_size;
	int				read_cont;
	t_element		element;
}					t_game;

typedef struct s_ray
{
	double			camera_x;
	double			raydir_x;
	double			raydir_y;
	int				map_x;
	int				map_y;
	double			sidedist_x;
	double			sidedist_y;
	int				step_x;
	int				step_y;
	double			deltadist_x;
	double			deltadist_y;
	double			perpwalldist;
}					t_ray;

typedef struct s_lines
{
	int				x;
	int				hit;
	int				side;
	int				lineheight;
	int				drawstart;
	int				drawend;
	int				tex_x;
	int				tex_y;
	double			wall_x;
	uint32_t		color;
}					t_lines;

typedef struct s_old
{
	double			dir_x;
	double			plane_x;
}					t_old;

typedef struct s_draw_line_params
{
	int				x;
	int				start;
	int				end;
}					t_draw_line_params;

// Initialization functions
void				init_all(t_game *game, t_element *element);

// Parse functions
int					check_extension(char *file);
int					check_header(t_game *game, t_element *element);
int					check_error(char *input, t_game *game, t_element *element);
void				get_hex_codes(t_game *game, t_element *element);
int					player_check(t_game *game, int i, int j);
int					check_is_closed(t_game *game, int i, int j);
int					check_spaces(t_game *game, int i, int j);
int					check_newline(t_game *game, int i, int j);
int					check_invalid_char(t_game *game, int i, int j);
int					player_and_map_check(t_game *game, int i, int j,
						int exit_count);
char				*get_content(char *line);
int					compare_and_assign(t_game *game, t_element *element, int i);

// Game functions
void				clear_image(mlx_image_t *image, uint32_t color);
void				draw_line(t_game *game, uint32_t color,
						t_draw_line_params *params);
void				move_player(mlx_key_data_t keydata, void *param);
void				update_and_render(void *param);
char				**initialize_map(char *mapData[], int mapHeight,
						t_game *game);
void				load_walls(t_game *game, t_element *element);
void				move_forward(t_game *game, double moveSpeed);
void				turn_mov(void *param);
void				key_a(mlx_key_data_t keydata, void *param);
void				side_mov(void *param);
void				draw_wall_with_texture(t_game *game, t_ray *ray, int x,
						t_lines *lines);
int					size_and_create_map(char *file, t_game *game);
void				create_map(t_game *game);
void				set_initial_orientation(t_game *game);

// Free functions
void				free_textures(t_game *game);
void				free_w_map(char **map);
void				free_element(t_element *element);
void				free_map(char **map, int map_height);

// Useful functions
void				*p_calloc(size_t count, size_t size);
void				ft_error(const char *message, t_game *game);

#endif