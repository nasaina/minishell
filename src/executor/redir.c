/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:21:58 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/16 17:15:44 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	do_redir(t_ast *ast)
{
	int			fd;
	t_redir		*redir;
	char		*file;

	redir = ast->cmd->redir;
	file = NULL;
	while (redir)
	{
		if (redir->type == HEREDOC)
		{
			file = ft_strjoin("/tmp/.tmp", ft_itoa(ast->file));
			fd = open(file, O_RDONLY);
			dup2(fd, STDIN_FILENO);
			close(fd);
			unlink(file);
		}
		else if (redir->type == OUT)
		{
			fd = open(redir->file, O_RDONLY | O_WRONLY | O_CREAT
				| O_TRUNC, 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redir->type == IN)
		{
			fd = open(redir->file, O_RDONLY);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (redir->type == APPEND)
		{
			fd = open(redir->file, O_RDONLY | O_WRONLY | O_APPEND, 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		redir = redir->next;
	}
}
