/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 10:24:02 by nandrian          #+#    #+#             */
/*   Updated: 2024/07/15 14:44:51 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_format(const char str, int *len, va_list list)
{
	if (str == 'c')
		ft_putchar_len(va_arg(list, int), len);
	else if (str == 's')
		ft_putstr_len(va_arg(list, char *), len);
	else if (str == 'p')
		ft_putadr(va_arg(list, void *), len);
	else if (str == 'd' || str == 'i')
		ft_putnbr_len(va_arg(list, int), len);
	else if (str == 'u')
		ft_putnbr_hex((unsigned int)va_arg(list, unsigned int), 10, 0, len);
	else if (str == 'x')
		ft_putnbr_hex(va_arg(list, int), 16, 0, len);
	else if (str == 'X')
		ft_putnbr_hex(va_arg(list, int), 16, 1, len);
	else if (str == '%')
	{
		write (1, "%", 1);
		*len += 1;
	}
}

int	ft_printf(const char *format, ...)
{
	va_list	list;
	int		i;
	int		len;

	len = 0;
	i = 0;
	va_start(list, format);
	while (format[i])
	{
		if (format[i] == '%' && ft_strchr_len("cspdi%uxX", format[i + 1]) == 1)
		{
			ft_format(format[i + 1], &len, list);
			i += 2;
		}
		else
		{
			ft_putchar_len(format[i], &len);
			i++;
		}
	}
	va_end(list);
	return (len);
}
