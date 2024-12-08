/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 14:22:23 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/08 16:35:09 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_heredoc	*create_heredoc(char *str)
{
	t_heredoc	*heredoc;

	heredoc = (t_heredoc *)malloc(sizeof(t_heredoc));
	if (!heredoc)
		return (NULL);
	heredoc->str = ft_strdup(str);
	heredoc->next = NULL;
	return (heredoc);
}

t_heredoc	*heredoc_last(t_heredoc *args)
{
	while (args->next)
		args = args->next;
	return (args);
}

void	add_heredoc_back(t_heredoc **heredoc, char *str)
{
	t_heredoc	*element;
	t_heredoc	*tmp;

	if (!str)
		return ;
	element = create_heredoc(str);
	if (*heredoc)
	{
		tmp = heredoc_last(*heredoc);
		tmp->next = element;
	}
	else
		*heredoc = element;
}

int	get_input(t_cmd *cmd)
{
	char		*str;
	int			fd[2];

	str = NULL;
	pipe(fd);
	while (1)
	{
		str = readline("heredoc > ");
		if (!ft_strcmp(cmd->redir->file, str))
			break ;
		else
		{
			ft_putstr_fd(str, fd[1]);
			ft_putstr_fd("\n", fd[1]);
			continue ;
		}
	}
	close(fd[1]);
	return (fd[0]);
}
