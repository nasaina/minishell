/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putadr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:51:27 by nandrian          #+#    #+#             */
/*   Updated: 2024/07/05 13:31:05 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_putnbr_adr(unsigned long int c, int *len)
{
	char	*str;

	str = "0123456789abcdef";
	if (c < 16)
		ft_putchar_len(str[c], len);
	else
	{
		ft_putnbr_adr(c / 16, len);
		ft_putnbr_adr(c % 16, len);
	}
}

void	ft_putadr(void *c, int *len)
{
	unsigned long int	out;

	out = (unsigned long int)c;
	if (out == 0)
	{
		write(1, "(nil)", 5);
		*len += 5;
	}
	else
	{
		write(1, "0x", 2);
		*len += 2;
		ft_putnbr_adr(out, len);
	}
}
