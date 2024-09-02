/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:04:35 by nandrian          #+#    #+#             */
/*   Updated: 2024/07/15 14:46:08 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_putstr_len(char *str, int *len)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		write (1, "(null)", 6);
		*len += 6;
	}
	else
	{
		while (str[i])
		{
			write(1, &str[i], 1);
			i++;
			*len += 1;
		}
	}
}
