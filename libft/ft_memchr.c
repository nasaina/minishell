/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 15:29:57 by nandrian          #+#    #+#             */
/*   Updated: 2024/03/27 06:36:28 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t size)
{
	char	*out;
	char	schr;

	out = (char *)s;
	schr = (char)c;
	while (size > 0)
	{
		if (*out == schr)
			return (out);
		out++;
		size--;
	}
	return (0);
}
