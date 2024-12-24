/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:21:58 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/24 09:53:41 by nandrian         ###   ########.fr       */
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

int	do_redir(t_ast *ast)
{
	int			i;
	int			status;
	t_redir		*redir;

	i = 0;
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
		i++;
		redir = redir->next;
	}
	return (status);
}
