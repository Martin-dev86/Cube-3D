/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:23:11 by jeandrad          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/01/13 18:43:21 by jeandrad         ###   ########.fr       */
=======
/*   Updated: 2024/12/20 18:02:22 by jeandrad         ###   ########.fr       */
>>>>>>> dbc6ffb (now the hardcoded game without textures works)
/*                                                                            */
/* ************************************************************************** */

#include "Includes/cub3d.h"

<<<<<<< HEAD
char	**read_map_from_file(const char *filename, int *mapHeight)
{
	int		fd;
	char	**map;
	char	*line;
	int		height;
	char	**new_map;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error al abrir el archivo");
		return (NULL);
	}
	map = NULL;
	height = 0;
	int capacity = 100; // Capacidad inicial para 100 líneas
	map = malloc(capacity * sizeof(char *));
	if (!map)
	{
		perror("Error al asignar memoria");
		close(fd);
		return (NULL);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		if (height >= capacity)
		{
			capacity *= 2;
			new_map = realloc(map, capacity * sizeof(char *));
			if (!new_map)
			{
				perror("Error al reasignar memoria");
				free(map);
				close(fd);
				return (NULL);
			}
			map = new_map;
		}
		map[height++] = line;
	}
	close(fd);
	*mapHeight = height;
	return (map);
}

void	free_map(char **map, int mapHeight)
{
	int	i;

	i = 0;
	while (i < mapHeight)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

char	**initialize_map(char **mapData, int mapHeight, t_game *game)
=======
void	free_map(char **map, int mapHeight)
{
	for (int i = 0; i < mapHeight; i++)
		free(map[i]);
	free(map);
}

char	**initialize_map(const char *mapData[], int mapHeight)
>>>>>>> dbc6ffb (now the hardcoded game without textures works)
{
	char	**map;

	map = malloc(mapHeight * sizeof(char *));
	if (!map)
		return (NULL);
	for (int i = 0; i < mapHeight; i++)
	{
		map[i] = strdup(mapData[i]);
		if (!map[i])
		{
			free_map(map, i);
			return (NULL);
		}
<<<<<<< HEAD
		for (int j = 0; j < ft_strlen(mapData[i]); j++)
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
			{
				game->posX = j + 0.5;
				game->posY = i + 0.5;
				game->initialOrientation = map[i][j];
				map[i][j] = '0';
					// Reemplazar la posición inicial con un espacio vacío
			}
		}
=======
>>>>>>> dbc6ffb (now the hardcoded game without textures works)
	}
	return (map);
}

<<<<<<< HEAD
void	set_initial_orientation(t_game *game)
{
	if (game->initialOrientation == 'N')
	{
		game->dirX = 0;
		game->dirY = -1;
		game->planeX = 0.66;
		game->planeY = 0;
	}
	else if (game->initialOrientation == 'S')
	{
		game->dirX = 0;
		game->dirY = 1;
		game->planeX = -0.66;
		game->planeY = 0;
	}
	else if (game->initialOrientation == 'E')
	{
		game->dirX = 1;
		game->dirY = 0;
		game->planeX = 0;
		game->planeY = 0.66;
	}
	else if (game->initialOrientation == 'W')
	{
		game->dirX = -1;
		game->dirY = 0;
		game->planeX = 0;
		game->planeY = -0.66;
	}
}

int	main(int argc, char **argv)
{
	t_game	game;
	int		mapHeight;
	int		mapWidth;
	char	**mapData;

	if (argc != 2)
	{
		fprintf(stderr, "Uso: %s <archivo_mapa.ber>\n", argv[0]);
		return (1);
	}
	// Leer el mapa desde el archivo
	mapData = read_map_from_file(argv[1], &mapHeight);
	if (!mapData)
	{
		fprintf(stderr, "Error: no se pudo leer el mapa del archivo.\n");
		return (1);
	}
	mapWidth = strlen(mapData[0]);
	game.mapHeight = mapHeight;
	game.mapWidth = mapWidth;
	game.worldMap = initialize_map(mapData, mapHeight, &game);
=======
int	main(void)
{
	t_game		game;
	const char	*mapData[] = {"11111111",
                              "10010001",
                              "10030101",
                              "10000001",
			                  "10000001",
                              "11111111"};
	int			mapHeight;
	int			mapWidth;

	// Datos iniciales del mapa
	mapHeight = sizeof(mapData) / sizeof(mapData[0]);
	mapWidth = strlen(mapData[0]);
	game.mapHeight = mapHeight;
	game.mapWidth = mapWidth;
	game.worldMap = initialize_map(mapData, mapHeight);
>>>>>>> dbc6ffb (now the hardcoded game without textures works)
	if (!game.worldMap)
	{
		fprintf(stderr, "Error: no se pudo inicializar el mapa.\n");
		return (1);
	}
<<<<<<< HEAD
	// Inicializar el juego a cero todo
=======
>>>>>>> dbc6ffb (now the hardcoded game without textures works)
	game.mlx = mlx_init(SCREENWIDTH, SCREENHEIGHT, "Cub3D", true);
	if (!game.mlx)
	{
		fprintf(stderr, "Error: no se pudo inicializar MLX42.\n");
		free_map(game.worldMap, mapHeight);
		return (1);
	}
	game.image = mlx_new_image(game.mlx, SCREENWIDTH, SCREENHEIGHT);
	if (!game.image)
	{
		fprintf(stderr, "Error: no se pudo crear la imagen.\n");
		mlx_terminate(game.mlx);
		free_map(game.worldMap, mapHeight);
		return (1);
	}
<<<<<<< HEAD
	// Cargar texturas
	load_walls(&game);
	// Establecer la orientación inicial del jugador
	set_initial_orientation(&game);
=======
	// Posición inicial del jugador
	game.posX = 1.5;
	game.posY = 1.5;
	game.dirX = -1;
	game.dirY = 0;
	game.planeX = 0;
	game.planeY = 0.66;
>>>>>>> dbc6ffb (now the hardcoded game without textures works)
	mlx_loop_hook(game.mlx, &update_and_render, &game);
	mlx_key_hook(game.mlx, &move_player, &game);
	mlx_loop(game.mlx);
	// Liberar recursos
	free_map(game.worldMap, mapHeight);
	mlx_terminate(game.mlx);
	return (0);
}
