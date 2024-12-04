/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:49:48 by cagarci2          #+#    #+#             */
/*   Updated: 2024/12/04 13:09:39 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		if (check_errors(argv[1]))
			return (1);
	}
	else
		return (ft_error("To many argument"));
	return (0);
}
