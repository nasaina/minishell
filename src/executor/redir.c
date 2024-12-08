/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:21:58 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/08 15:09:36 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	do_redir(t_cmd *cmd)
{
	int	fd;

	if (cmd->redir->type == OUT)
	{
		fd = open(cmd->redir->file, O_RDONLY | O_WRONLY | O_CREAT
			| O_TRUNC, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (cmd->redir->type == IN)
	{
		fd = open(cmd->redir->file, O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (cmd->redir->type == APPEND)
	{
		fd = open(cmd->redir->file, O_RDONLY | O_WRONLY | O_APPEND, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (cmd->redir->type == HEREDOC)
		get_input(cmd);
}
