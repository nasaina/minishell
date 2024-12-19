/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 11:38:08 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/19 14:33:43 by nandrian         ###   ########.fr       */
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
		result = join_free(result, tmp, 0);
		free(tmp);
	}
	return (result);
}
