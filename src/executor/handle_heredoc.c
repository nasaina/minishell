/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 14:22:23 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/10 16:23:02 by nandrian         ###   ########.fr       */
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
	int		j;
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
		j = 0;
		wrd = malloc(count + 1);
		while (j < count)
			wrd[j++] = str[i++];
		wrd[j] = '\0';
		add_chunks_back(&chunks, wrd, type);
		while (str[i] == 32)
			i++;
	}
	free(str);
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
	t_redir *heredoc;
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
		chunks = chunks->next;
	}
	return (heredoc);
}

int	is_expandable(char	*str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

char	*expand_heredoc(char *file, char *str, t_export *export)
{
	int		i;
	int		j;
	char	*name;
	char	*value;
	char	*result;

	if (!str)
		return (NULL);
	if (is_expandable(file))
		return (str);
	result = NULL;
	if (is_variable(str))
	{
		i = 0;
		while (str[i])
		{
			if (str[i] == '$' && str[i + 1] != '"' && str[i + 1] != '\'' && str[i + 1])
			{
				name = get_var_name(str, i);
				i++;
				if (isdigit(name[0]))
				{
					i++;
					continue ;
				}
				value = ms_getenv(name, export);
				if (value)
				{
					result = ft_strjoin(result, value);
					free(value);
				}
				j = 0;
				while (j < (int)ft_strlen(name))
				{
					j++;
					i++;
				}
				free (name);
			}
			result = join_char(result, str[i]);
			i++;
		}
		return (result);
	}
	return (str);
}


char	*ignore_quote(char	*str)
{
	char	*result;
	int		count;
	int		i;
	
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			count++;
		i++;
	}
	result = malloc(ft_strlen(str) - count + 1);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			i++;
		result[count] = str[i];
		i++;
		count++;
	}
	result[count] = 0;
	return (result);
}

int	get_input(t_redir *heredoc, t_export *export)
{
	char	*str;
	char	*expander;
	char	*name;
	int		fd;
	int		status;

	str = NULL;
	fd = open(".tmp", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (is_expandable(heredoc->file))
		status = 0;
	name = ignore_quote(heredoc->file);
	while (1)
	{
		str = readline("heredoc > ");
		if (!ft_strcmp(name, str))
			break ;
		else
		{
			expander = expand_heredoc(heredoc->file, str, export);
			if (expander)
				ft_putstr_fd(expander, fd);
			ft_putstr_fd("\n", fd);
			continue ;
		}
	}
	close(fd);
	return (fd);
}
