/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 07:10:06 by nandrian          #+#    #+#             */
/*   Updated: 2024/03/24 17:02:46 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	char	*out1;
	char	*out2;

	i = 1;
	out1 = (char *)s1;
	out2 = (char *)s2;
	if (n > 0)
	{
		while (*out1 == *out2 && *out1 != '\0' && i < n)
		{
			out1++;
			out2++;
			i++;
		}
		if (*out1 == *out2)
			return (0);
		else
			return ((unsigned char)*out1 - (unsigned char)*out2);
	}
	else
		return (0);
}
