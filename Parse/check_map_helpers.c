/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:54:33 by jeandrad          #+#    #+#             */
/*   Updated: 2025/01/29 16:40:11 by jeandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

int	player_check(t_game *game, int i, int j)
{
	if (game->world_map[i][j] == 'E' || game->world_map[i][j] == 'S'
		|| game->world_map[i][j] == 'W' || game->world_map[i][j] == 'N')
		return (1);
	return (0);
}

int	check_is_closed(t_game *game, int i, int j)
{
	if (game->world_map[i][j] == 'S' || game->world_map[i][j] == '0'
		|| game->world_map[i][j] == 'W' || game->world_map[i][j] == 'N'
		|| game->world_map[i][j] == 'E')
		return (1);
	return (0);
}

int	check_spaces(t_game *game, int i, int j)
{
	if (!game->world_map[i + 1] || !game->world_map[i][j + 1]
		|| game->world_map[i - 1][j] == ' ' || game->world_map[i + 1][j] == ' '
		|| game->world_map[i][j - 1] == ' ' || game->world_map[i][j + 1] == ' ')
		return (1);
	return (0);
}

int	check_newline(t_game *game, int i, int j)
{
	if (!game->world_map[i + 1] || !game->world_map[i][j + 1]
		|| game->world_map[i - 1][j] == '\n' || game->world_map[i
		+ 1][j] == '\n' || game->world_map[i][j - 1] == '\n'
		|| game->world_map[i][j + 1] == '\n')
		return (1);
	return (0);
}

int	check_invalid_char(t_game *game, int i, int j)
{
	if (game->world_map[i][j] != '1' && game->world_map[i][j] != ' '
		&& game->world_map[i][j] != 'N' && game->world_map[i][j] != 'W'
		&& game->world_map[i][j] != 'S' && game->world_map[i][j] != 'E')
		return (1);
	return (0);
}
