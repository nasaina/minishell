/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 14:22:23 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/17 10:38:50 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

char	*hdoc_expander(char *str, t_export *export)
{
	int		i;
	char	*name;
	char	*result;

	i = 0;
	result = NULL;
	if(!str && !str[i])
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$' && !char_isquote(str[i + 1]) && str[i + 1])
		{
			if (name_token(str, &i, &name))
				continue ;
			export_value(&result, &i, export, name);
		}
		if (str[i])
		{
		
			result = join_char(result, str[i]);
			i++;
		}
	}
	return (result);
}

char	*expand_heredoc(char *file, char *str, t_export *export)
{
	char	*result;

	if (!str)
		return (NULL);
	result = NULL;
	if (!is_expandable(file) && is_variable(str))
		result = hdoc_expander(str, export);
	else
		result = ft_strdup(str);
	return (result);
}

int	quote_count(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (char_isquote(str[i]))
			count++;
		i++;
	}
	return (count);
}

char	*ignore_quote(char	*str)
{
	char	*result;
	int		count;
	int		i;

	count = quote_count(str);
	result = malloc(ft_strlen(str) - count + 1);
	i = 0;
	count = 0;
	while (str[i])
	{
		while (char_isquote(str[i]) && str[i])
			i++;
		if (str[i])
		{
			result[count] = str[i];
			count++;
			i++;
		}
	}
	result[count] = 0;
	return (result);
}

int	get_input(t_heredoc *heredoc, t_redir *tmp)
{
	char	*str;
	char	*expander;

	str = NULL;
	heredoc->fd = open(heredoc->file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	while (1)
	{
		str = readline("heredoc > ");
		if (!ft_strcmp(heredoc->name, str))
		{
			free(heredoc->name);
			free(str);
			break ;
		}
		else
		{
			expander = expand_heredoc(tmp->file, str, heredoc->export);
			if (expander)
			{
				ft_putstr_fd(expander, heredoc->fd);
				free(expander);
			}
			ft_putstr_fd("\n", heredoc->fd);
		}
		free(str);
		str = NULL;
	}
	return (heredoc->fd);
}

void	free_heredoc_data(t_heredoc *heredoc)
{
	free_redir(heredoc->lst);
	free_export(heredoc->export);
	free(heredoc->name);
	unlink(heredoc->file);
	free(heredoc->file);
	free(heredoc);
}
