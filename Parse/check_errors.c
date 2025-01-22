/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:38:33 by cagarci2          #+#    #+#             */
/*   Updated: 2025/01/22 19:59:06 by cagarci2         ###   ########.fr       */
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
	int		i;
	int		config_count;
	//char	*config_found[6] = {0};

	i = 0;
	config_count = 0;
	while (config_count < 6)
	{
		if (ft_strncmp(&game->map[i][0], "NO ", 3) == 0 && !element->north)
		{
			config_count++;
			element->north = get_content(game->map[i]);
			printf("TEXTURA MAPA === %s\n", game->map[i]);
		}
		else if (ft_strncmp(&game->map[i][0], "SO ", 3) == 0 && !element->south)
		{
			config_count++;
			element->south = get_content(game->map[i]);
			printf("ESTE ES 2\n");
			printf("TEXTURA MAPA === %s\n", game->map[i]);
		}
		else if (ft_strncmp(&game->map[i][0], "WE ", 3) == 0 && !element->west)
		{
			config_count++;
			element->west = get_content(game->map[i]);
			printf("ESTE ES 3\n");
			printf("TEXTURA MAPA === %s\n", game->map[i]);
		}
		else if (ft_strncmp(&game->map[i][0], "EA ", 3) == 0 && !element->east)
		{
			config_count++;
			element->east = get_content(game->map[i]);
			printf("ESTE ES 4\n");
			printf("TEXTURA MAPA === %s\n", game->map[i]);
		}
		else if (ft_strncmp(&game->map[i][0], "F ", 2) == 0 && !element->floor)
		{
			config_count++;
			element->floor = get_content(game->map[i]);
			printf("ESTE ES 5\n");
			printf("TEXTURA MAPA === %s\n", game->map[i]);
		}
		else if (ft_strncmp(&game->map[i][0], "C ", 2) == 0 && !element->ceiling)
		{
			config_count++;
			element->ceiling = get_content(game->map[i]);
			printf("ESTE ES 6\n");
			printf("TEXTURA MAPA === %s\n", game->map[i]);
		}
		// else if (game->map[i][0] != '\n' && game->map[i][0] != ' ')
		// {
		// 	printf("Error: Invalid configuration line: %s\n",
		// 		game->map[i]);
		// 	exit(1);
		// }
		printf("TEXTURA MAPA FUERA === %s\n", game->map[i]);
		printf("ESTE ES EL COUNT === %d\n", config_count);
		i++;
	}
	if (config_count < 6)
	{
		printf("Error: Missing textures or colors in the header.\n");
		exit(EXIT_FAILURE);
	}
	return (1);
}


// int	check_content(t_game *game, t_element *element)
// {
//     int	i;

//     i = 0;
//     while (game->map[i] && game->map[i][0] != '1')
//     {
//         if (game->map[i][0] == 'N' && game->map[i][1] == 'O')
// 			element->north = get_content(game->map[i]);
//         else if (game->map[i][0] == 'S' && game->map[i][1] == 'O')
//             element->south = get_content(game->map[i]);
//         else if (game->map[i][0] == 'W' && game->map[i][1] == 'E')
//             element->west = get_content(game->map[i]);
//         else if (game->map[i][0] == 'E' && game->map[i][1] == 'A')
//             element->east = get_content(game->map[i]);
//         else if (game->map[i][0] == 'F')
//             element->floor = get_content(game->map[i]);
//         else if (game->map[i][0] == 'C')
//             element->ceiling = get_content(game->map[i]);
//         else if (game->map[i][0] != '\n' && game->map[i][0] != ' ')
//         {
//             printf("Error: Invalid line in header: %s\n", game->map[i]);
//             exit(EXIT_FAILURE);
//         }
//         i++;
//     }
//     return (1);
// }

void print_map(char **map, int map_height) 
{
	int i = 0;
	printf("Map height is: %i\n", map_height);
	printf("MAP:\n");
    while (i < map_height && map[i])
	{
        printf("%s\n", map[i]);
		i++;
    }
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
	{
		printf("Error: Cannot open file %s.\n", file);
		exit (EXIT_FAILURE);
	}
	while (game->read_cont > 0)
	{
		game->read_cont = read(fd, buffer, sizeof(buffer));
		if (game->read_cont < 0)
			return (close(fd), printf("Error: Reading error.\n"), 0);
		game->file_size += game->read_cont;
	}
	close(fd);
	map_temp = malloc(game->file_size + 1);
	if (!map_temp)
		return (printf("Error: Memory allocation failed.\n"), 0);
	fd = open(file, O_RDONLY);
	game->read_cont = read(fd, map_temp, game->file_size);
	map_temp[game->read_cont] = '\0';
	close(fd);
	game->map = ft_split(map_temp, '\n');
	// Para debuguear
	print_map(game->map, game->file_size);
	printf("MAP ENDED\n");
	// Hasta aquí
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
	// if (!check_content(game, element))
	// 	return (0);
	return (1);
}
