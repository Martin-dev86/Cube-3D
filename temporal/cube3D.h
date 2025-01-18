/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:48:34 by cagarci2          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/12/30 12:55:26 by cagarci2         ###   ########.fr       */
=======
/*   Updated: 2024/12/11 18:03:24 by jeandrad         ###   ########.fr       */
>>>>>>> Execute
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_3D_H
# define CUBE_3D_H

# include <fcntl.h>
# include <memory.h>
# include <stdint.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "../Library/Libft/libft.h"
# include "../Library/ft_printf/ft_printf.h"

# define NO 'N'
# define SO 'S'
# define WO 'W'
# define EO 'E'
# define WALL '1'
# define FLOOR '0'

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdint.h>
# include <string.h>
# include <unistd.h>
# include <stdint.h>
# include "../Library/Libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"


// Todo esto deberia ir en una structura con valores fijos
# define MAPWIDTH 10
# define MAPHEIGHT 10
# define SCREENWIDTH 640
# define SCREENHEIGHT 480
# define MOVE_SPEED 0.1
# define ROT_SPEED 0.05

// mi estructura de juego
typedef struct 
{
    mlx_t *mlx;
    mlx_image_t *image;
    double posX, posY;    // Posición del jugador
    double dirX, dirY;    // Dirección de la cámara
    double planeX, planeY; // Plano de la cámara (para la perspectiva)
    int worldMap[MAPWIDTH][MAPHEIGHT];
} t_game;

//funciones
void clear_image(mlx_image_t *image, uint32_t color);
void draw_line(t_game *game, int x, int start, int end, uint32_t color);
void move_player(mlx_key_data_t keydata, void *param);
void update_and_render(void *param);

typedef struct s_game_3d
{
	int		file_size;
	int		read_cont;
	char	**maps;
<<<<<<< HEAD
}	t_game_3d;
typedef struct s_element
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	*floor;
	char	*ceiling;
}	t_element;
=======
} t_game_3d;
>>>>>>> Master

int	check_extension(char *file);
int check_header(t_game_3d *game_3d);
int	size_and_create_map(char *file, t_game_3d *game_3d);
int	check_error(char input, t_game_3d *game_3d);

#endif
