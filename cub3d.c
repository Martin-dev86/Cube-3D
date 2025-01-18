/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:23:11 by jeandrad          #+#    #+#             */
/*   Updated: 2025/01/18 19:29:04 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/cub3d.h"

void print_parsed_values(t_element *element) 
{
    printf("North texture: %s\n", element->north);
    printf("South texture: %s\n", element->south);
    printf("West texture: %s\n", element->west);
    printf("East texture: %s\n", element->east);
    printf("Floor color: %s\n", element->floor);
    printf("Ceiling color: %s\n", element->ceiling);
}

// char	**read_map_from_file(const char *filename, int *map_height)
// {
// 	int		fd;
// 	char	**map;
// 	char	*line;
// 	int		height;
// 	char	**new_map;

// 	fd = open(filename, O_RDONLY);
// 	if (fd < 0)
// 	{
// 		perror("Error al abrir el archivo");
// 		return (NULL);
// 	}
// 	map = NULL;
// 	height = 0;
// 	int capacity = 100; // Capacidad inicial para 100 líneas
// 	map = malloc(capacity * sizeof(char *));
// 	if (!map)
// 	{
// 		perror("Error al asignar memoria");
// 		close(fd);
// 		return (NULL);
// 	}
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		if (height >= capacity)
// 		{
// 			capacity *= 2;
// 			new_map = realloc(map, capacity * sizeof(char *));
// 			if (!new_map)
// 			{
// 				perror("Error al reasignar memoria");
// 				free(map);
// 				close(fd);
// 				return (NULL);
// 			}
// 			map = new_map;
// 		}
// 		map[height++] = line;
// 	}
// 	close(fd);
// 	*map_height = height;
// 	return (map);
// }

void	free_map(char **map, int map_height)
{
	int	i;

	i = 0;
	while (i < map_height)
	{
		free(map[i]);
		i++;
	}
}

char	**initialize_map(char **mapData, int map_height, t_game *game)
{
	char	**map;

	map = malloc(map_height * sizeof(char *));
	if (!map)
		return (NULL);
	for (int i = 0; i < map_height; i++)
	{
		map[i] = strdup(mapData[i]);
		if (!map[i])
		{
			free_map(map, i);
			return (NULL);
		}
		for (int j = 0; j < ft_strlen(mapData[i]); j++)
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
			{
				game->pos_x = j + 0.5;
				game->pos_y = i + 0.5;
				game->initial_orientation = map[i][j];
				map[i][j] = '0';
					// Reemplazar la posición inicial con un espacio vacío
			}
		}
	}
	return (map);
}

void	set_initial_orientation(t_game *game)
{
	if (game->initial_orientation == 'N')
	{
		game->dir_x = 0;
		game->dir_y = -1;
		game->plane_x = 0.66;
		game->plane_y = 0;
	}
	else if (game->initial_orientation == 'S')
	{
		game->dir_x = 0;
		game->dir_y = 1;
		game->plane_x = -0.66;
		game->plane_y = 0;
	}
	else if (game->initial_orientation == 'E')
	{
		game->dir_x = 1;
		game->dir_y = 0;
		game->plane_x = 0;
		game->plane_y = 0.66;
	}
	else if (game->initial_orientation == 'W')
	{
		game->dir_x = -1;
		game->dir_y = 0;
		game->plane_x = 0;
		game->plane_y = -0.66;
	}
}

int	main(int argc, char **argv)
{
	t_game		game;
	t_element	element;
	int			map_height;
	int			mapWidth;
	char		**mapData;

	map_height = 0;
	if (argc != 2)
	{
		fprintf(stderr, "Uso: %s <archivo_mapa.ber>\n", argv[0]);
		return (1);
	}
	// Comprobar errores y crear mapa
	if ( (!check_error(argv[1], &game, &element)))
	{
		fprintf(stderr, "Error de mapa");
		return(1);
	}
	mapData = game.world_map; 
	if (!mapData)
	{
		fprintf(stderr, "Error: no se pudo leer el mapa del archivo.\n");
		return (1);
	}
	// Leer el mapa desde el archivo
	//mapData = read_map_from_file(argv[1], &map_height);
	// if (!mapData)
	// {
	// 	fprintf(stderr, "Error: no se pudo leer el mapa del archivo.\n");
	// 	return (1);
	// }
	mapWidth = ft_strlen(mapData[0]);
	game.map_height = map_height;
	game.map_width = mapWidth;
	printf("Mapa leído: %d x %d\n", mapWidth, map_height);
	game.world_map = initialize_map(mapData, map_height, &game);
	printf("mapa inicializado\n");
	if (!game.world_map)
	{
		fprintf(stderr, "Error: no se pudo inicializar el mapa.\n");
		return (1);
	}
	printf("Entra\n");
	// Inicializar el juego a cero todo
	game.mlx = mlx_init(SCREENWIDTH, SCREENHEIGHT, "Cub3D", true);
	printf("Entra\n");
	if (!game.mlx)
	{
		fprintf(stderr, "Error: no se pudo inicializar MLX42.\n");
		free_map(game.world_map, map_height);
		return (1);
	}
	game.image = mlx_new_image(game.mlx, SCREENWIDTH, SCREENHEIGHT);
	if (!game.image)
	{
		fprintf(stderr, "Error: no se pudo crear la imagen.\n");
		mlx_terminate(game.mlx);
		free_map(game.world_map, map_height);
		return (1);
	}
	printf("Entra load walls\n");
	load_walls(&game);
	printf("sale load walls\n");
	printf("Print the values:\n");
	print_parsed_values(&element);
	// Establecer la orientación inicial del jugador
	set_initial_orientation(&game);
	printf("player orientation done\n");
	mlx_loop_hook(game.mlx, &update_and_render, &game);
	mlx_key_hook(game.mlx, &move_player, &game);
	mlx_loop(game.mlx);
	// Liberar recursos
	free_map(game.world_map, map_height);
	free_textures(&game);
	mlx_terminate(game.mlx);
	return (0);
}
