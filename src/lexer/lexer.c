/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 09:34:29 by nandrian          #+#    #+#             */
/*   Updated: 2024/10/07 09:35:10 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_word(char c)
{
	char	*str;

	str = "<>| \'";
	if (!ft_strchr(str, c))
		return (1);
	return (0);
}

int	count_args(int count, char *str, int i, t_type *type)
{
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
	else if (str[i] == 39)
		count = is_quote(str, i, type);
	else
		count = one_word(str, i, type);
	return (count);
}

t_chunk	*lexing(t_chunk *chunks, char *str)
{
	int		i;
	int		j;
	int		count;
	char	*wrd;
	t_type	type;

	i = 0;
	while (str[i])
	{
		while (str[i] == 32)
			i++;
		count = count_args(count, str, i, &type);
		j = 0;
		wrd = malloc(count + 1);
		while (j < count)
			wrd[j++] = str[i++];
		wrd[j] = '\0';
		add_chunks_back(&chunks, wrd, type);
		while (str[i] == 32)
			i++;
	}
	return (chunks);
}
