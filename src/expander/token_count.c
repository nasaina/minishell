/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 11:31:38 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/13 11:32:16 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_var_name(char *str, int i)
{
	int		j;
	int		len;
	char	*name;

	len = 0;
	if (str[i] == '$')
		i++;
	j = i;
	while (str[i] != 32 && str[i] != 34 && str[i] != 39 && str[i])
	{
		i++;
		len++;
	}
	name = malloc(len + 1);
	i = 0;
	while (i < len)
		name[i++] = str[j++];
	name[i] = 0;
	return (name);
}

int	no_quote(char *str, int i)
{
	int		count;

	count = 0;
	while (str[i] != 34 && str[i] != 39 && str[i])
	{
		count++;
		i++;
	}
	return (count);
}

int	quote_simple(char *str, int i)
{
	int	count;

	count = 0;
	while (str[i] && str[i] != '\'')
	{
		i++;
		count++;
	}
	return (count);
}

int	quote_double(char *str, int i)
{
	int	count;

	count = 0;
	while (str[i] && str[i] != '"')
	{
		i++;
		count++;
	}
	return (count);
}
