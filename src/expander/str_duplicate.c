/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_duplicate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 11:35:29 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/13 11:35:57 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*str_insert(char *str, int count, int *i)
{
	char	*new;
	int		j;

	j = 0;
	new = malloc(count + 1);
	while (j < count)
	{
		new[j] = str[*i];
		j++;
		*i += 1;
	}
	new[j] = 0;
	return (new);
}

char	*join_char(char *str, char c)
{
	char	*result;
	char	*value;
	int		len;

	if (!str)
		result = ft_strdup(&c);
	else
	{
		len = ft_strlen(str);
		result = malloc(len + 2);
		ft_strlcpy(result, str, len + 1);
		result[len] = c;
		result[len + 1] = 0;
	}
	value = ft_strdup(result);
	free(result);
	return (value);
}

int	char_isquote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

int	ignore_value(char	*str, char **result, int *i, int *status)
{
	if (str[*i] == '"')
		*status = 1;
	if (str[*i] == '\'' && *status == 0)
	{
		*result = join_char(*result, str[*i]);
		*i += 1;
		while (str[*i] != '\'' && str[*i])
		{
			*result = join_char(*result, str[*i]);
			*i += 1;
		}
	}
	if (str[*i] == '$' && char_isquote(str[*i + 1]) && str[*i + 2])
	{
		*i += 1;
		return (1);
	}
	return (0);
}
