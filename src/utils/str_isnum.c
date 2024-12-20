/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_isnum.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:03:14 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/20 14:17:29 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	str_isnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 32 || str[i] == '\t')
		{
			while (str[i] && (str[i] == 32 || str[i] == '\t'))
				i++;
			while (str[i] && str[i] != 32 && str[i] != '\t')
				i++;
			while (str[i] && (str[i] == 32 || str[i] == '\t'))
				i++;
			if (str[i])
			{
				printf("too many args\n");
				exit(2);
			}
		}
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
