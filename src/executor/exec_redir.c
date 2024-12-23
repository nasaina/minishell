/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 08:34:21 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/23 08:34:30 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	redir_out(t_ast *ast, t_redir *redir)
{
	int		fd;

	fd = open(redir->file, O_RDONLY | O_WRONLY | O_CREAT
			| O_TRUNC, 0644);
	redir_error(fd, redir->file, ast);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

int	redir_in(t_ast *ast, t_redir *redir)
{
	int		fd;

	fd = open(redir->file, O_RDONLY);
	redir_error(fd, redir->file, ast);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (1);
}

int	redir_heredoc(t_ast *ast)
{
	char	*file;
	int		fd;

	file = NULL;
	file = join_free("/tmp/.hd_tmp", ft_itoa(ast->file), 1);
	fd = open(file, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	unlink(file);
	return (1);
}

int	redir_append(t_ast *ast, t_redir *redir)
{
	int		fd;

	fd = open(redir->file, O_RDONLY | O_WRONLY | O_CREAT | O_APPEND, 0644);
	redir_error(fd, redir->file, ast);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}
