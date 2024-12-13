/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:30:07 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/13 15:13:38 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	hdoc_oneword(char *str, int i, t_type *type)
{
	int	count;

	count = 0;
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
	*type = WORD;
	return (count);
}

int	hdoc_count(int count, char *str, int i, t_type *type)
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
	else
		count = hdoc_oneword(str, i, type);
	return (count);
}

t_chunk	*hdoc_token(char *str)
{
	int		i;
	int		count;
	char	*wrd;
	t_chunk	*chunks;
	t_type	type;

	i = 0;
	chunks = NULL;
	while (str[i])
	{
		while (str[i] == 32)
			i++;
		count = hdoc_count(count, str, i, &type);
		wrd = str_insert(str, count, &i);
		add_chunks_back(&chunks, wrd, type);
		free(wrd);
		while (str[i] == 32)
			i++;
	}
	return (chunks);
}

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

int	heredoc_check(t_chunk *chunks)
{
	while (chunks)
	{
		if (chunks->type == HEREDOC)
			return (1);
		chunks = chunks->next;
	}
	return (0);
}

t_redir	*expand_hdoc(char *str)
{
	t_redir	*heredoc;
	t_chunk	*chunks;

	chunks = hdoc_token(str);
	heredoc = NULL;
	while (chunks && chunks->next)
	{
		if (chunks->type == HEREDOC)
		{
			add_redir_back(&heredoc, chunks->next->str, HEREDOC);
			chunks = chunks->next;
		}
		if (chunks->type == PIPE)
			add_redir_back(&heredoc, "PIPE", PIPE);
		chunks = chunks->next;
	}
	return (heredoc);
}

