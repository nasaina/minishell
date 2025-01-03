/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 14:22:23 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/26 14:38:07 by nandrian         ###   ########.fr       */
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

char	*hdoc_expander(char *str, t_env *env)
{
	int		i;
	char	*result;

	i = 0;
	result = NULL;
	if (!str && !str[i])
		return (NULL);
	while (str[i])
	{
		if (heredoc_input(str, &i, env, &result))
			continue ;
	}
	return (result);
}

int	get_heredoc_value(t_heredoc **heredoc, char *str, t_redir *tmp)
{
	char	*expander;

	if (!str)
	{
		free((*heredoc)->name);
		return (1);
	}
	if (!ft_strcmp((*heredoc)->name, str))
	{
		free((*heredoc)->name);
		free(str);
		return (1);
	}
	else
	{
		expander = expand_heredoc(tmp->file, str, (*heredoc)->env);
		if (expander)
		{
			ft_putstr_fd(expander, (*heredoc)->fd);
			free(expander);
		}
		ft_putstr_fd("\n", (*heredoc)->fd);
	}
	return (0);
}

void	get_input(t_heredoc *heredoc, t_redir *tmp)
{
	char	*str;

	str = NULL;
	heredoc->fd = open(heredoc->file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	get_here_data(heredoc);
	while (1)
	{
		str = readline("heredoc > ");
		if (get_heredoc_value(&heredoc, str, tmp))
			break ;
		free(str);
		str = NULL;
	}
}

void	free_heredoc_data(t_heredoc *heredoc)
{
	free_redir(heredoc->lst);
	free_env(heredoc->env);
	free(heredoc->name);
	unlink(heredoc->file);
	free(heredoc->file);
	free(heredoc);
}
