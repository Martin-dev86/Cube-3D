/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:38:33 by cagarci2          #+#    #+#             */
/*   Updated: 2025/02/06 14:10:37 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

int	check_header(t_game *game, t_element *element)
{
	int	i;
	int	config_count;

	i = 0;
	config_count = 0;
	while (game->world_map[i] && config_count < 6)
	{
		compare_and_assign(game, element, i);
		config_count++;
		i++;
	}
	if (config_count < 6)
		ft_error("Missing configuration\n", game);
	return (1);
}

int	check_maps(t_game *game)
{
	int	i;
	int	j;
	int	exit_count;

	exit_count = 0;
	j = 0;
	i = 6;
	while (game->world_map[i])
	{
		j = 0;
		while (game->world_map[i][j])
		{
			exit_count = player_and_map_check(game, i, j, exit_count);
			j++;
		}
		i++;
	}
	if (exit_count != 1)
		ft_error("Invalid number of players\n", game);
	return (1);
}

int	calculate_file_size(char *file, t_game *game)
{
	int		fd;
	char	buffer[1024];

	game->file_size = 0;
	game->read_cont = 1;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_error("File not found.", game);
	while (game->read_cont > 0)
	{
		game->read_cont = read(fd, buffer, sizeof(buffer));
		if (game->read_cont < 0)
		{
			close(fd);
			ft_error("File reading failed.", game);
		}
		game->file_size += game->read_cont;
	}
	close(fd);
	return (game->file_size);
}

int	size_and_create_map(char *file, t_game *game)
{
	int		fd;
	char	*map_temp;

	calculate_file_size(file, game);
	map_temp = p_calloc(game->file_size + 1, sizeof(char));
	fd = open(file, O_RDONLY);
	game->read_cont = read(fd, map_temp, game->file_size);
	map_temp[game->read_cont] = '\0';
	close(fd);
	game->world_map = ft_split(map_temp, '\n');
	free(map_temp);
	return (1);
}

int	check_error(char *input, t_game *game, t_element *element)
{
	if (!check_extension(input))
		return (0);
	if (!size_and_create_map(input, game))
		return (0);
	if (!check_header(game, element))
		return (0);
	if (!check_maps(game))
		return (0);
	return (1);
}
