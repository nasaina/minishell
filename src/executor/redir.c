/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:21:58 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/20 08:46:30 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	redir_error(int fd, char *str, t_ast *ast)
{
	if (fd < 0)
	{
		perror(str);
		free_ast(ast);
		exit (EXIT_FAILURE);
	}
}

void	redir_in(t_ast *ast)
{
	int		fd;
	char	*file;
	t_redir	*redir;

	redir = ast->cmd->redir;
	if (redir->type == HEREDOC)
	{
		file = ft_strjoin("/tmp/.hd_tmp", ft_itoa(ast->file));
		fd = open(file, O_RDONLY);
		redir_error(fd, "heredoc", ast);
		dup2(fd, STDIN_FILENO);
		close(fd);
		unlink(file);
	}
	else if (redir->type == IN)
	{
		fd = open(redir->file, O_RDONLY);
		redir_error(fd, redir->file, ast);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}

void	redir_out(t_ast *ast)
{
	int		fd;
	t_redir	*redir;

	redir = ast->cmd->redir;
	if (redir->type == OUT)
	{
		fd = open(redir->file, O_RDONLY | O_WRONLY | O_CREAT
				| O_TRUNC, 0644);
		redir_error(fd, redir->file, ast);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (redir->type == APPEND)
	{
		fd = open(redir->file, O_RDONLY | O_WRONLY | O_APPEND, 0644);
		redir_error(fd, redir->file, ast);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

void	do_redir(t_ast *ast)
{
	char		*file;
	t_redir		*redir;

	redir = ast->cmd->redir;
	file = NULL;
	while (redir)
	{
		if (redir->type == HEREDOC || redir->type == IN)
			redir_in(ast);
		if (redir->type == OUT || redir->type == APPEND)
			redir_out(ast);
		redir = redir->next;
	}
}
