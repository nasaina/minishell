/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 11:01:43 by nandrian          #+#    #+#             */
/*   Updated: 2024/03/23 09:39:30 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	in;
	size_t	out;

	i = 0;
	j = 0;
	while (dst[j])
		j++;
	out = j;
	in = ft_strlen(src);
	if (size == 0 || size <= out)
		return (in + size);
	while (src[i] && i < size - out -1)
	{
		dst[j] = src[i];
		j++;
		i++;
	}
	dst[j] = '\0';
	return (out + in);
}
