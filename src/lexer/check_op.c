/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:10:31 by nandrian          #+#    #+#             */
/*   Updated: 2024/09/16 10:57:12 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	one_word(char *str, int i, t_type *type)
{
	int	count;

	count = 0;
	while (is_word(str[i]))
	{
		count++;
		i++;
	}
	*type = WORD;
	return (count);
}

int	is_append(char *str, int i, t_type *type)
{
	int	count;

	count = 0;
	if (str[i] == '>')
	{
		*type = OUT;
		count++;
		i++;
	}
	if (str[i] == '>')
	{
		*type = APPEND;
		count++;
		i++;
	}
	return (count);
}

int	is_heredoc(char *str, int i, t_type *type)
{
	int	count;

	count = 0;
	if (str[i] == '<')
	{
		*type = IN;
		count++;
		i++;
	}
	if (str[i] == '>')
	{
		*type = NONE;
		count++;
		i++;
	}
	if (str[i] == '<')
	{
		*type = HEREDOC;
		count++;
		i++;
	}
	return (count);
}