/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:48:34 by cagarci2          #+#    #+#             */
/*   Updated: 2024/12/04 13:54:09 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_3D_H
# define CUBE_3D_H

# include <fcntl.h>
# include <memory.h>
# include <stdint.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include "MLX42.h"
# include "libft.h"
# include "ft_printf.h"

# define NO 'N'
# define SO 'S'
# define WO 'W'
# define EO 'E'
# define WALL '1'
# define FLOOR '0'

typedef struct game_3d
{
	int		file_size;
	int		read_cont;
	char	**maps;
}

#endif
