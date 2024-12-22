/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:57:53 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/22 16:59:33 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	hdoc_countsimple(char *str, int i, t_type *type)
{
	int	count;

	count = 0;
	count++;
	i++;
	while (str[i] && str[i] != '\'')
	{
		count++;
		i++;
	}
	if (str[i] && str[i] == '\'')
	{
		count++;
		i++;
	}
	*type = WORD;
	return (count);
}

int	hdoc_countdouble(char *str, int i, t_type *type)
{
	int	count;

	count = 0;
	count++;
	i++;
	while (str[i] && str[i] != '"')
	{
		count++;
		i++;
	}
	if (str[i] && str[i] == '"')
	{
		count++;
		i++;
	}
	*type = WORD;
	return (count);
}

int	hdoc_oneword(char *str, int i, t_type *type)
{
	int	count;

	count = 0;
	if (str[i] && str[i] == '\'')
		return (hdoc_countsimple(str, i, type));
	else if (str[i] == '"')
		return (hdoc_countdouble(str, i, type));
	else
	{
		while (str[i] != 32 && str[i] && is_word(str[i]))
		{
			if (str[i] == 32)
			{
				count = 0;
				i++;
			}
			else
				count++;
			i++;
		}
	}
	*type = WORD;
	return (count);
}

int	hdoc_count(char *str, int i, t_type *type)
{
	int	count;

	count = 0;
	if (!str)
		return (0);
	if ((str[i]) == '>')
		count = is_append(str, i, type);
	else if (str[i] == '<')
		count = is_heredoc(str, i, type);
	else if (str[i] == '|')
	{
		count = 1;
		*type = PIPE;
	}
	else
		count = hdoc_oneword(str, i, type);
	return (count);
}
