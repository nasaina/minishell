/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:17:43 by nandrian          #+#    #+#             */
/*   Updated: 2024/09/16 13:35:43 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_variable(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

char	*get_variable(char *str)
{
	char	*name;
	int		i;
	int		j;

	i = 0;
	while (str[i] != '$')
		i++;
	i++;
	name = malloc((ft_strlen(str) - i) + 1);
	j = 0;
	while (str[i])
	{
		name[j] = str[i];
		i++;
		j++;
	}
	name[j] = '\0';
	return (name);	
}

void	expander(t_chunk *chunks)
{
	(void)chunks;
}
