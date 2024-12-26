/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 10:55:31 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/26 10:57:55 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	read_input(char **str, t_env *env)
{
	*str = NULL;
	*str = ft_readline();
	if (!*str)
	{
		ft_putendl_fd("exit", 1);
		unlink("/tmp/.ms_status");
		free_env(env);
		exit(0);
	}
	if (is_error(*str) || is_void(*str))
		return (1);
	return (0);
}

int	check_file(t_expander *expander)
{
	t_expander	*tmp;

	tmp = expander;
	while (tmp)
	{
		if (tmp->type != WORD && tmp->type != PIPE)
		{
			tmp = tmp->next;
			if (tmp && tmp->cmd[0] == 0)
				return (1);
		}
		if (!tmp)
			break ;
		tmp = tmp->next;
	}
	return (0);
}

int	check_pipe(t_chunk *chunks)
{
	t_chunk	*tmp;

	tmp = chunks;
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			tmp = tmp->next;
			if (tmp && tmp->type == PIPE)
			{
				ft_putstr_fd("minishell :syntax error\n", 2);
				ms_writestatus(2);
				free_chunks(chunks);
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int	redir_syntax(t_chunk *chunks)
{
	t_chunk	*tmp;

	if (check_pipe(chunks))
		return (1);
	tmp = chunks;
	while (tmp)
	{
		if (tmp->type != WORD && tmp->type != PIPE)
		{
			tmp = tmp->next;
			if (tmp && tmp->type != WORD)
			{
				ft_putstr_fd("minishell :syntax error\n", 2);
				ms_writestatus(2);
				free_chunks(chunks);
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int	heredoc_start(char *str, t_chunk *chunks, t_env *env)
{
	int	heredoc_status;

	if (one_hd(str))
	{
		heredoc_status = heredoc_built(str, env, chunks);
		ms_writestatus(heredoc_status);
		if (heredoc_status)
		{
			free_chunks(chunks);
			return (1);
		}
	}
	return (0);
}
