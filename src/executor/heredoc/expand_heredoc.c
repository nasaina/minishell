/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:30:07 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/22 17:02:55 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_hdstatus(int status, t_heredoc *data)
{
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 130)
		{
			free(data);
			return (130);
		}
		else
		{
			free(data);
			return (0);
		}
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

t_chunk	*hdoc_token(char *str)
{
	int		i;
	int		count;
	char	*wrd;
	t_chunk	*chunks;
	t_type	type;

	i = 0;
	chunks = NULL;
	type = 0;
	while (str[i])
	{
		while (str[i] == 32)
			i++;
		count = hdoc_count(str, i, &type);
		wrd = str_insert(str, count, &i);
		add_chunks_back(&chunks, wrd, type);
		free(wrd);
		while (str[i] == 32)
			i++;
	}
	return (chunks);
}

t_redir	*expand_hdoc(char *str)
{
	t_redir	*heredoc;
	t_chunk	*chunks;
	t_chunk	*tmp;

	tmp = hdoc_token(str);
	heredoc = NULL;
	chunks = tmp;
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
	free_chunks(tmp);
	return (heredoc);
}
