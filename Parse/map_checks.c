/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:11:31 by jeandrad          #+#    #+#             */
/*   Updated: 2025/01/29 16:41:34 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

int	check_extension(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len < 4 || file[len - 1] != 'b' || file[len - 2] != 'u'
		|| file[len - 3] != 'c' || file[len - 4] != '.')
	{
		printf("Error: Invalid file extension. Expected '.cub'.\n");
		return (0);
	}
	return (1);
}

char	*get_content(char *line)
{
	char	*content;
	char	*result;

	content = ft_strchr(line, ' ');
	if (!content)
	{
		printf("Error: Missing content after identifier: %s\n", line);
		exit(EXIT_FAILURE);
	}
	result = ft_strtrim(content, " \t");
	return (result);
}

int	compare_and_assign(t_game *game, t_element *element, int i)
{
	if (ft_strncmp(&game->world_map[i][0], "NO ", 3) == 0)
		element->north = get_content(game->world_map[i]);
	else if (ft_strncmp(&game->world_map[i][0], "SO ", 3) == 0)
		element->south = get_content(game->world_map[i]);
	else if (ft_strncmp(&game->world_map[i][0], "WE ", 3) == 0)
		element->west = get_content(game->world_map[i]);
	else if (ft_strncmp(&game->world_map[i][0], "EA ", 3) == 0)
		element->east = get_content(game->world_map[i]);
	else if (ft_strncmp(&game->world_map[i][0], "F ", 2) == 0)
		element->floor = get_content(game->world_map[i]);
	else if (ft_strncmp(&game->world_map[i][0], "C ", 2) == 0)
		element->ceiling = get_content(game->world_map[i]);
	else if (game->world_map[i][0] != '\n' && game->world_map[i][0] != ' ')
		ft_error("Error: Invalid configuration\n", game);
	return (1);
}

int	player_and_map_check(t_game *game, int i, int j, int exit_count)
{
	if (player_check(game, i, j) == 1)
		exit_count++;
	if (check_is_closed(game, i, j) == 1)
	{
		if (check_spaces(game, i, j) == 1)
			ft_error("Map not closed\n", game);
		if (check_newline(game, i, j) == 1)
			ft_error("Map not closed\n", game);
	}
	else if (check_invalid_char(game, i, j) == 1)
		ft_error("Invalid character in the map\n", game);
	return (exit_count);
}
