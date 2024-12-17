/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 11:38:08 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/17 13:38:00 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	name_token(char *str, int *i, char **name)
{
	*name = get_var_name(str, *i);
	*i += 1;
	if (isdigit(*name[0]))
	{
		*i += 1;
		return (1);
	}
	return (0);
}

char	*handle_dquote(char *str, int *i)
{
	int		count;
	char	*result;

	*i += 1;
	count = quote_double(str, *i);
	result = str_insert(str, count, i);
	if (str[*i] == '"')
		*i += 1;
	return (result);
}

char	*handle_squote(char *str, int *i)
{
	int		count;
	char	*result;

	*i += 1;
	count = quote_simple(str, *i);
	result = str_insert(str, count, i);
	if (str[*i] == '\'')
		*i += 1;
	return (result);
}

int	dquote_status(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

char	*join_free1(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	j = 0;
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	if (s1)
	{
		while (s1[i])
		{
			str[i] = s1[i];
			i++;
		}
	}
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}

char	*get_command(char *str)
{
	int		i;
	int		count;
	char	*tmp;
	char	*result;

	i = 0;
	result = NULL;
	while (str[i])
	{
		if (str[i] == '\'')
			tmp = handle_squote(str, &i);
		else if (str[i] == '"')
			tmp = handle_dquote(str, &i);
		else
		{
			count = no_quote(str, i);
			tmp = str_insert(str, count, &i);
		}
		result = join_free1(result, tmp);
		free(tmp);
	}
	return (result);
}
