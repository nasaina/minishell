/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 08:34:21 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/24 14:39:36 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	redir_out(t_ast *ast, t_redir *redir)
{
	int		fd;

	(void)ast;
	if (redir->file == NULL || redir->file[0] == 0)
	{
		ft_putstr_fd("minishell : No such file or directory\n", 2);
		return (1);
	}
	fd = open(redir->file, O_RDONLY | O_WRONLY | O_CREAT
			| O_TRUNC, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

int	redir_in(t_ast *ast, t_redir *redir)
{
	int		fd;
	int		status;

	fd = open(redir->file, O_RDONLY);
	status = redir_error(fd, redir->file, ast);
	if (status < 0)
		return (status);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (1);
}

int	redir_heredoc(t_ast *ast)
{
	char	*file;
	int		fd;

	file = NULL;
	file = join_free(".hd_tmp", ft_itoa(ast->file), 1);
	fd = open(file, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (1);
}

int	redir_append(t_ast *ast, t_redir *redir)
{
	int		fd;

	(void)ast;
	if (redir->file == NULL || redir->file[0] == 0)
	{
		ft_putstr_fd("minishell : No such file or directory\n", 2);
		return (1);
	}
	fd = open(redir->file, O_RDONLY | O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}
