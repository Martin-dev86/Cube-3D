/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:38:33 by cagarci2          #+#    #+#             */
/*   Updated: 2025/01/28 17:57:41 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

int	check_extension(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len < 4 || file[len - 1] != 'b' || file[len - 2] != 'u' || file[len
		- 3] != 'c' || file[len - 4] != '.')
	{
		printf("Error: Invalid file extension. Expected '.cub'.\n");
		return (0);
	}
	return (1);
}

char	*get_content(char *line)
{
	char	*content;

	content = ft_strchr(line, ' ');
	if (!content)
	{
		printf("Error: Missing content after identifier: %s\n", line);
		exit(EXIT_FAILURE);
	}
	return (ft_strdup(ft_strtrim(content, " \t")));
}
int	check_header(t_game *game, t_element *element)
{
	int	i;
	int	config_count;

	i = 0;
	config_count = 0;
	while (game->world_map[i] && config_count < 6)
	{
		if (ft_strncmp(&game->world_map[i][0], "NO ", 3) == 0)
		{
			config_count++;
			element->north = get_content(game->world_map[i]);
			printf("ESTE ES 1\n");
			printf("TEXTURA MAPA === %s\n", game->world_map[i]);
		}
		else if (ft_strncmp(&game->world_map[i][0], "SO ", 3) == 0)
		{
			config_count++;
			element->south = get_content(game->world_map[i]);
			printf("ESTE ES 2\n");
			printf("TEXTURA MAPA === %s\n", game->world_map[i]);
		}
		else if (ft_strncmp(&game->world_map[i][0], "WE ", 3) == 0)
		{
			config_count++;
			element->west = get_content(game->world_map[i]);
			printf("ESTE ES 3\n");
			printf("TEXTURA MAPA === %s\n", game->world_map[i]);
		}
		else if (ft_strncmp(&game->world_map[i][0], "EA ", 3) == 0)
		{
			config_count++;
			element->east = get_content(game->world_map[i]);
			printf("ESTE ES 4\n");
			printf("TEXTURA MAPA === %s\n", game->world_map[i]);
		}
		else if (ft_strncmp(&game->world_map[i][0], "F ", 2) == 0)
		{
			config_count++;
			element->floor = get_content(game->world_map[i]);
			printf("ESTE ES 5\n");
			printf("TEXTURA MAPA === %s\n", game->world_map[i]);
		}
		else if (ft_strncmp(&game->world_map[i][0], "C ", 2) == 0)
		{
			config_count++;
			element->ceiling = get_content(game->world_map[i]);
			printf("ESTE ES 6\n");
			printf("TEXTURA MAPA === %s\n", game->world_map[i]);
		}
		else if (game->world_map[i][0] != '\n' && game->world_map[i][0] != ' ')
		{
			printf("Error: Invalid configuration line\n");
			exit(1);
		}
		i++;
	}
	if (config_count < 6)
	{
		printf("Error: Missing textures or colors in the header.\n");
		exit(EXIT_FAILURE);
	}
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
			if (strspn(game->world_map[i], " ") == strlen(game->world_map[i]))
				continue ;
			while (game->world_map[i][j])
			{
				if (game->world_map[i][j] == 'E')
					exit_count++;
				else if (game->world_map[i][j] == '0' || game->world_map[i][j] == '0' ||
					game->world_map[i][j] == '0' || game->world_map[i][j] == '0' ||
						game->world_map[i][j] == '0')
				{
					// Verificar que 0 esté completamente rodeado por 1 o 0
					if (!game->world_map[i + 1] || !game->world_map[i][j + 1] ||
						game->world_map[i - 1][j] == ' ' ||
							game->world_map[i + 1][j] == ' ' ||
								game->world_map[i][j - 1] == ' ' ||
									game->world_map[i][j + 1] == ' ')
						ft_error("Error: Map not closed\n", game);
					if (!game->world_map[i + 1] || j == 0
						|| !game->world_map[i][j + 1] || game->world_map[i
						- 1][j] == '\n' || game->world_map[i + 1][j] == '\n'
						|| game->world_map[i][j - 1] == '\n'
						|| game->world_map[i][j + 1] == '\n')
						ft_error("Error: Map not closed\n", game);
				}
				else if (game->world_map[i][j] != '1'
					&& game->world_map[i][j] != ' '
					&& game->world_map[i][j] != 'E')
					ft_error("Error: Invalid character in the map\n", game);
				j++;
			}
		}
		i++;
	}
	if (exit_count != 1)
		ft_error("Error: Invalid number of players\n", game);
	return (1);
}

int	size_and_create_map(char *file, t_game *game)
{
	int		fd;
	char	buffer[1024];
	char	*map_temp;

	game->file_size = 0;
	game->read_cont = 1;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_error("Error: File not found.", game);
	while (game->read_cont > 0)
	{
		game->read_cont = read(fd, buffer, sizeof(buffer));
		if (game->read_cont < 0)
			{
				close(fd);
				ft_error("Error: File reading failed.", game);
			}
		game->file_size += game->read_cont;
	}
	close(fd);
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
	if (!check_maps(game))
		return (0);
	if (!check_header(game, element))
		return (0);
	return (1);
}
