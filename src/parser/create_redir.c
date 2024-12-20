/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:15:32 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/20 07:59:18 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_redir	*create_redir(char *file, t_type type)
{
	t_redir	*redir;

	redir = (t_redir *)malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file = ft_strdup(file);
	redir->next = NULL;
	return (redir);
}

t_redir	*redir_last(t_redir *args)
{
	while (args->next)
		args = args->next;
	return (args);
}

void	add_redir_back(t_redir **redir, char *file, t_type type)
{
	t_redir	*element;
	t_redir	*tmp;

	element = create_redir(file, type);
	if (*redir)
	{
		tmp = redir_last(*redir);
		tmp->next = element;
	}
	else
		*redir = element;
}
