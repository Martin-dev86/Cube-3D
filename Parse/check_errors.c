/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:52:43 by cagarci2          #+#    #+#             */
/*   Updated: 2024/12/04 13:53:47 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

int	check_extension(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (file[len - 1] != 'b' || file[len - 2] != 'u'
		|| file[len - 3] != 'c' || file[len - 4] != '.')
		return (0);
	return (1);
}
int check_header(t_game_3d *game_3d)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	while(i < 6 || game->maps[j][1] != '1' || game->maps[j][1] != ' ')
	{
		if(game->maps[j] == '\n')
			j++;
		else
			i++;
	}
	if (i == 6)
		return (1);
	return(0);
}
// int check_textures_and_colours(t_game_3d *game_3d)
// {

// }

int	size_file(char *file, t_game_3d *game_3d)
{
	int		fd;
	char	buffer[1024];
	char	*map_temp;

	game_3d->file_size = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (close(fd), ft_printf("Error: Reading error."), 0);
	while (game_3d->read_cont > 0)
	{
		game_3d->read_cont = read(fd, buffer, sizeof(buffer));
		game_3d->file_size += game_3d->read_cont;
	}
	if (game_3d->read_cont == -1)
		return (close(fd), 0);
	close (fd);
	map_temp = malloc(game->file_size + 1);
	if (!map_temp)
		return (ft_printf("%s Error: Reading error.", file), 0);
	fd = open(file, O_RDONLY);
	game->read_cont = read(fd, map_temp, game->file_size);
	if (game->read_cont <= 0 || !map_temp)
		return (close(fd), free(map_temp), 3);
	map_temp[game->read_cont] = '\0';
	close(fd);
	game_3d->maps = ft_split(map_temp, '\n');
	return (1);
}

int	check_error(char input, t_game_3d *game_3d)
{
	if (!(check_extension(input)))
		return (1);
	if (!(size_file(input, game_3d)))
		return (1);
	if (!(check_header(game_3d)))
		return (1);

}
