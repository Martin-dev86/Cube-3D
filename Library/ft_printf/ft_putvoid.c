/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putvoid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 11:19:46 by cagarci2          #+#    #+#             */
/*   Updated: 2023/12/21 12:41:38 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putvoid(unsigned long long p)
{
	int		count;
	char	*str;

	str = "0x";
	count = 0;
	count += ft_putstr(str);
	if (count == -1)
		return (-1);
	count += ft_puthex(p, 'x');
	return (count);
}
