/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 12:19:59 by nandrian          #+#    #+#             */
/*   Updated: 2024/03/24 15:25:45 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;
	char	*out1;
	char	*out2;

	i = 0;
	out1 = (char *)s1;
	out2 = (char *)s2;
	if (!*out2)
		return ((char *)out1);
	while (out1[i] && i < n)
	{
		j = 0;
		while (out1[i + j] == out2[j] && out1[i + j] && i + j < n)
		{
			j++;
			if (!out2[j])
				return ((char *)out1 + i);
		}
		i++;
	}
	return (NULL);
}
