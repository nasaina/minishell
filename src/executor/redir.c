/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:21:58 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/25 09:51:42 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	redir_error(int fd, char *str, t_ast *ast)
{
	(void)ast;
	if (fd < 0)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (-1);
	}
	return (0);
}

int	do_redir(t_ast *ast)
{
	int			i;
	int			status;
	t_redir		*redir;

	i = 0;
	status = -1;
	redir = ast->cmd->redir;
	while (redir)
	{
		if (redir->type == IN)
			status = redir_in(ast, redir);
		else if (redir->type == OUT)
			status = redir_out(ast, redir);
		else if (redir->type == APPEND)
			status = redir_append(ast, redir);
		else if (redir->type == HEREDOC)
			status = redir_heredoc(ast);
		if (status < 0)
			return (-1);
		i++;
		redir = redir->next;
	}
	return (status);
}
