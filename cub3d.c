/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:23:11 by jeandrad          #+#    #+#             */
/*   Updated: 2025/01/25 19:55:47 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/cub3d.h"

void	print_parsed_values(t_element *element)
{
	printf("North texture: %s\n", element->north);
	printf("South texture: %s\n", element->south);
	printf("West texture: %s\n", element->west);
	printf("East texture: %s\n", element->east);
	printf("Floor color: %s\n", element->floor);
	printf("Ceiling color: %s\n", element->ceiling);
}

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
	int		i;
	int		j;

	map = p_calloc(map_height + 1, sizeof(char *));
	i = 0;
	while (i < map_height)
	{
		map[i] = strdup(mapData[i]);
		if (!map[i])
		{
			free_map(map, i);
			return (NULL);
		}
		j = 0;
		while (j < ft_strlen(mapData[i]))
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
			{
				game->pos_x = j + 0.5;
				game->pos_y = i + 0.5;
				game->initial_orientation = map[i][j];
				map[i][j] = '0';
			}
			j++;
		}
		i++;
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

	map_height = 0;
	if (argc != 2)
	{
		printf("Uso: %s <archivo_mapa.ber>\n", argv[0]);
		return (1);
	}
	if ((!check_error(argv[1], &game, &element)))
	{
		printf("Error de mapa");
		return (1);
	}
	create_map(&game);
	print_map(game.world_map, game.map_height);
	if (!game.world_map)
	{
		printf("Error: no se pudo inicializar el mapa.\n");
		return (1);
	}
	game.world_map = initialize_map(game.world_map, game.map_height, &game);
	printf("mapa inicializado\n");
	if (!game.world_map)
	{
		printf("Error: no se pudo inicializar el mapa.\n");
		return (1);
	}
	game.mlx = mlx_init(SCREENWIDTH, SCREENHEIGHT, "Cub3D", true);
	if (!game.mlx)
	{
		printf("Error: no se pudo inicializar MLX42.\n");
		free_map(game.world_map, map_height);
		return (1);
	}
	game.image = mlx_new_image(game.mlx, SCREENWIDTH, SCREENHEIGHT);
	if (!game.image)
	{
		printf("Error: no se pudo crear la imagen.\n");
		mlx_terminate(game.mlx);
		free_map(game.world_map, map_height);
		return (1);
	}
	load_walls(&game, &element);
	print_parsed_values(&element);
	set_initial_orientation(&game);
	get_hex_codes(&game, &element);
	mlx_loop_hook(game.mlx, &update_and_render, &game);
	mlx_key_hook(game.mlx, &move_player, &game);
	mlx_loop(game.mlx);
	free_map(game.world_map, map_height);
	free_textures(&game);
	mlx_terminate(game.mlx);
	return (0);
}
