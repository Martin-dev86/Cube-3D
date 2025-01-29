/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:23:11 by jeandrad          #+#    #+#             */
/*   Updated: 2025/01/29 19:49:21 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/cub3d.h"

void	initial_orient(t_game *game, char **map, int i, int j)
{
	game->pos_x = j + 0.5;
	game->pos_y = i + 0.5;
	game->initial_orientation = map[i][j];
	map[i][j] = '0';
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
		map[i] = ft_strdup(mapData[i]);
		if (!map[i])
		{
			free_map(map);
			return (NULL);
		}
		j = 0;
		while (j < ft_strlen(mapData[i]))
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
				initial_orient(game, map, i, j);
			j++;
		}
		i++;
	}
	return (free_map(mapData), map);
}

void	initial_check(int argc, char **argv, t_game *game, t_element *element)
{
	if (argc != 2)
		ft_error("Error: Invalid number of arguments.", game);
	if ((!check_error(argv[1], game, element)))
		ft_error("Error: Invalid map.", game);
	create_map(game);
	if (!game->world_map)
		ft_error("Error: Cannot create the map.", game);
	game->world_map = initialize_map(game->world_map, game->map_height, game);
	if (!game->world_map)
		ft_error("Error: Cannot initialize the map.", game);
	game->mlx = mlx_init(SCREENWIDTH, SCREENHEIGHT, "Cub3D", true);
	if (!game->mlx)
		ft_error("Error: Cannot initialize the mlx.", game);
	game->image = mlx_new_image(game->mlx, SCREENWIDTH, SCREENHEIGHT);
	if (!game->image)
	{
		mlx_terminate(game->mlx);
		ft_error("Error: Cannot create the image.", game);
	}
}

int	main(int argc, char **argv)
{
	t_game		game;
	t_element	element;

	initial_check(argc, argv, &game, &element);
	load_walls(&game, &element);
	set_initial_orientation(&game);
	get_hex_codes(&game, &element);
	mlx_loop_hook(game.mlx, &update_and_render, &game);
	mlx_key_hook(game.mlx, &move_player, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	free_textures(&game);
	free_element(&element);
	free_map(game.world_map);
	return (0);
}
