/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:23:11 by jeandrad          #+#    #+#             */
/*   Updated: 2025/01/28 15:38:50 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/cub3d.h"

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
		ft_error("Error: Invalid number of arguments.", &game);
	if ((!check_error(argv[1], &game, &element)))
		ft_error("Error: Invalid map.", &game);
	create_map(&game);
	if (!game.world_map)
		ft_error("Error: Cannot create the map.", &game);
	game.world_map = initialize_map(game.world_map, game.map_height, &game);
	if (!game.world_map)
		ft_error("Error: Cannot initialize the map.", &game);
	game.mlx = mlx_init(SCREENWIDTH, SCREENHEIGHT, "Cub3D", true);
	if(!game.mlx)
		ft_error("Error: Cannot initialize the mlx.", &game);
	game.image = mlx_new_image(game.mlx, SCREENWIDTH, SCREENHEIGHT);
	if (!game.image)
	{
		mlx_terminate(game.mlx);
		ft_error("Error: Cannot create the image.", &game);
	}
	load_walls(&game, &element);
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
