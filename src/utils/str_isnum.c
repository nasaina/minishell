/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_isnum.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:03:14 by nandrian          #+#    #+#             */
/*   Updated: 2024/10/09 08:51:57 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	str_isnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	table_isnum(char **str)
{
	if (!str_isnum(str[1]))
		return (0);
	return (1);
}
