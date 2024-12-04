/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 10:34:39 by cagarci2          #+#    #+#             */
/*   Updated: 2023/12/21 13:30:44 by cagarci2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_format(char simbol, va_list ap)
{
	int	count;

	count = 0;
	if (simbol == 'c')
		count += ft_putchar(va_arg(ap, int));
	else if (simbol == 's')
		count += ft_putstr(va_arg(ap, char *));
	else if (simbol == 'p')
		count += ft_putvoid(va_arg(ap, unsigned long long));
	else if (simbol == 'd' || simbol == 'i')
		count += ft_putdigit(va_arg(ap, int));
	else if (simbol == 'u')
		count += ft_putunsign(va_arg(ap, unsigned int));
	else if (simbol == 'x')
		count += ft_puthex(va_arg(ap, unsigned int), 'x');
	else if (simbol == 'X')
		count += ft_puthex(va_arg(ap, unsigned int), 'X');
	else
		count += write(1, &simbol, 1);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;

	va_start(ap, format);
	count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			count += print_format(*(++format), ap);
			if (count == -1)
				return (-1);
		}
		else
		{
			count += ft_putchar(*format);
			if (count == -1)
				return (-1);
		}
		++format;
	}
	va_end(ap);
	return (count);
}
