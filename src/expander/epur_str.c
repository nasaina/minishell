/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epur_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:35:31 by nandrian          #+#    #+#             */
/*   Updated: 2024/09/26 15:28:16 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	count_space(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == 32)
			i++;
		if (str[i] != 32 && str[i])
			count++;
		while (str[i] != 32)
			i++;
		i++;
	}
	return (count - 1);
}		

int	count_char(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != 32)
			count++;
		i++;
	}
	return (count);
}

void	ignore_space(char *str, int *i)
{
	while (str[*i] == 32)
		*i += 1;
}

char	*epur_str(char *str)
{
	int	i;
	int	j;
	char	*result;

	i = 0;
	j = 0;
	result = malloc(count_char(str) + count_space(str) + 1);
	while (str[i])
	{
		ignore_space(str, &i);
		while (str[i] != 32)
		{
			result[j] = str[i];
			j++;
			i++;
		}
		ignore_space(str, &i);
		if (str[i] != 32 && str[i])
		{
			result[j] = 32;
			j++;
		}
	}
	result[j] = '\0';
	return (result);
}
