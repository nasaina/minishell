/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_space.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:31:33 by nandrian          #+#    #+#             */
/*   Updated: 2024/09/02 11:03:42 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_space(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != 32)
	{
		if (str[i] == 32)
			return (1);
		i++;
	}
	return (0);
}

