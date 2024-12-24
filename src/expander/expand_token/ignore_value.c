/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ignore_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 13:54:57 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/24 09:50:59 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ignore_double(char *str, int *i)
{
	if (str[*i] && str[*i] == '$' && str[*i + 1]
		&& str[*i + 1] == '$')
	{
		*i += 2;
		return (1);
	}
	return (0);
}

int	ignore_digit(char *str, int *i)
{
	if (str[*i] && str[*i] == '$'
		&& str[*i + 1] && ft_isdigit(str[*i + 1]))
	{
		*i += 2;
		return (1);
	}
	return (0);
}

void	ignore_single(char *str, int *i, char **result)
{
	if (str[*i] && str[*i] == '$' && ((str[*i + 1]
				&& char_isquote(str[*i + 1])) || !str[*i + 1]))
	{
		*result = join_char(*result, '$');
		*i += 1;
	}
}

void	ignore_special(char *str, char **result, int *i)
{
	extract_status(result, i, str);
	ignore_double(str, i);
	ignore_digit(str, i);
	ignore_single(str, i, result);
}

char	**ignore_split(char *str, int *i, int *status, t_chunk **token)
{
	char	**split;
	char	*tmp;

	split = NULL;
	tmp = extract_noquote(str, status, i);
	if (tmp == NULL)
		return (NULL);
	split = ft_split_tab(tmp);
	free(tmp);
	if (check_split(split))
	{
		add_chunks_back(token, split[0], WORD);
		free(split[0]);
		free(split);
		*status = 0;
		return (NULL);
	}
	return (split);
}
