/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 11:55:55 by nandrian          #+#    #+#             */
/*   Updated: 2024/07/05 13:46:45 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

size_t	ft_strlen_len(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strchr_len(const char *s, int c)
{
	size_t	len;
	char	in;

	len = ft_strlen_len(s);
	in = (char)c;
	while (len > 0 && *s != in)
	{
		s++;
		len--;
	}
	if (*s == in)
		return (1);
	return (0);
}
