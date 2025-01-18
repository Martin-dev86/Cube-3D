/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeandrad <jeandrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:38:33 by cagarci2          #+#    #+#             */
/*   Updated: 2025/01/18 18:03:17 by jeandrad         ###   ########.fr       */
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

int check_header(t_game *game)
{
    int i;
    int config_count;
    char *config_found[6] = {0};

    i = 0;
    config_count = 0;
    while (game->world_map[i] && config_count < 6)
    {
        if (game->world_map[i][0] == 'NO' && !config_found[0])
            config_found[0] = game->world_map[i];
        else if (game->world_map[i][0] == 'SO' && !config_found[1])
            config_found[1] = game->world_map[i];
        else if (game->world_map[i][0] == 'WE' && !config_found[2])
            config_found[2] = game->world_map[i];
        else if (game->world_map[i][0] == 'EA' && !config_found[3])
            config_found[3] = game->world_map[i];
        else if (game->world_map[i][0] == 'F' && !config_found[4])
            config_found[4] = game->world_map[i];
        else if (game->world_map[i][0] == 'C' && !config_found[5])
            config_found[5] = game->world_map[i];
        else if (game->world_map[i][0] != '\n' && game->world_map[i][0] != ' ')
        {
            printf("Error: Invalid configuration line: %s\n", game->world_map[i]);
            exit (1);
        }
        i++;
    }
    if (config_count < 6)
    {
        printf("Error: Missing textures or colors in the header.\n");
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

int	check_content(t_game *game, t_element *element)
{
	int	i;

	i = 0;
	while (game->world_map[i] && game->world_map[i][0] != '1')
	{
		if (game->world_map[i][0] == 'N')
			element->north = get_content(game->world_map[i]);
		else if (game->world_map[i][0] == 'S')
			element->south = get_content(game->world_map[i]);
		else if (game->world_map[i][0] == 'W')
			element->west = get_content(game->world_map[i]);
		else if (game->world_map[i][0] == 'E')
			element->east = get_content(game->world_map[i]);
		else if (game->world_map[i][0] == 'F')
			element->floor = get_content(game->world_map[i]);
		else if (game->world_map[i][0] == 'C')
			element->ceiling = get_content(game->world_map[i]);
		else if (game->world_map[i][0] != '\n')
		{
			printf("Error: Invalid line in header: %s\n", game->world_map[i]);
			return (0);
		}
		i++;
	}
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
	{
		printf("Error: Cannot open file %s.\n", file);
		return (0);
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
	game->world_map = ft_split(map_temp, '\n');
	free(map_temp);
	return (1);
}

int	check_error(char *input, t_game *game, t_element *element)
{
	if (!(check_extension(input)))
		return (0);
	if (!(size_and_create_map(input, game)))
		return (0);
	if (!(check_header(game)))
		return (0);
	if (!(check_content(game, element)))
		return (0);
	return (1);
}
