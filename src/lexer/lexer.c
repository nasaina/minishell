/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 09:34:29 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/24 08:58:31 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_word(char c)
{
	char	*str;

	str = "<>|";
	if (!ft_strchr(str, c))
		return (1);
	return (0);
}

int	count_args(int count, char *str, int i, t_type *type)
{
	if (!str && !str[i])
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
		count = one_word(str, i, type);
	return (count);
}

void	skip_space(char *str, int *i)
{
	while ((str[*i] == 32 || str[*i] == '\t') && str[*i])
		*i += 1;
}

t_chunk	*lexing(char *str)
{
	int		i;
	int		count;
	char	*wrd;
	t_chunk	*chunks;
	t_type	type;

	i = 0;
	chunks = NULL;
	if (!str)
		return (NULL);
	while (str[i])
	{
		skip_space(str, &i);
		if (i >= (int)ft_strlen(str))
			break ;
		count = count_args(count, str, i, &type);
		wrd = str_insert(str, count, &i);
		add_chunks_back(&chunks, wrd, type);
		free(wrd);
		if (i >= (int)ft_strlen(str))
			break ;
		skip_space(str, &i);
	}
	return (chunks);
}
