/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:21:58 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/23 16:50:41 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	redir_error(int fd, char *str, t_ast *ast)
{
	if (fd < 0)
	{
		perror(str);
		free_ast(ast);
		exit(EXIT_FAILURE);
	}
}

void	do_redir(t_ast *ast)
{
	int			i;
	t_redir		*redir;

	i = 0;
	redir = ast->cmd->redir;
	while (redir)
	{
		if (redir->type == IN)
			redir_in(ast, redir);
		else if (redir->type == OUT)
			redir_out(ast, redir);
		else if (redir->type == APPEND)
			redir_append(ast, redir);
		else if (redir->type == HEREDOC)
			redir_heredoc(ast);
		i++;
		redir = redir->next;
	}
}
