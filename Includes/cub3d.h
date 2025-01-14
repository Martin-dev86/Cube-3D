/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:22:18 by jeandrad          #+#    #+#             */
/*   Updated: 2025/01/14 15:30:05 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../Library/Libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include <stdbool.h>
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

// For the wall textures
typedef struct s_texture
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*east;
}					t_textures;

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
	char			**world_map;
	int				map_width;
	int				map_height;
	char			initial_orientation;
	uint32_t		color;
}					t_game;

typedef struct
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

typedef struct lines
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

// funciones
void				clear_image(mlx_image_t *image, uint32_t color);
void				draw_line(t_game *game, int x, int start, int end,
						uint32_t color);
void				move_player(mlx_key_data_t keydata, void *param);
void				update_and_render(void *param);
char				**initialize_map(char *mapData[], int mapHeight,
						t_game *game);
void				free_map(char **map, int mapHeight);
void				load_walls(t_game *game);
void				move_forward(t_game *game, double moveSpeed);
void				turn_mov(mlx_key_data_t keydata, void *param);
void				key_a(mlx_key_data_t keydata, void *param);
void				side_mov(mlx_key_data_t keydata, void *param);
void				draw_wall_with_texture(t_game *game, t_ray *ray, int x,
						t_lines *lines);

#endif