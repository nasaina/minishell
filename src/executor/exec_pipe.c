/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 13:29:57 by maandria          #+#    #+#             */
/*   Updated: 2024/12/03 16:40:08 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	pipe_check(t_ast *ast, t_export *export, t_expander *expander, char *str, char **env)
{
	if (ast->type == 1)
	{
		exec_pipe(ast, export, expander, str, env);
	}
	else
		check_cmd(ast, export, env);
}

void	exec_pipe(t_ast *ast, t_export *export, t_expander *expander, char *str, char **env)
{
	pid_t	pid;
	int		status;
	int		pipe_fds[2];

	pipe(pipe_fds);
	pid = fork();
	if (pid < 0)
		perror("fork");
	else if (pid == 0)
	{
		if (ast->left)
		{
			dup2(pipe_fds[1], 1);
			pipe_check(ast->left, export, expander, str, env);
			close(pipe_fds[1]);
			close(pipe_fds[0]);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		 if (fork() == 0)
		{ 
			if (ast->right)
			{
				dup2(pipe_fds[0], 0);
				pipe_check(ast->right, export, expander, str, env);
				close(pipe_fds[1]);
				close(pipe_fds[0]);
				exit (EXIT_FAILURE);
			}
		}
		waitpid(pid, &status, 0);
	}
}
// void	pipe_fd(t_ast *ast, int *pipe_fds)
// {
// 	if (ast->left)
// 	{
// 		dup2(pipe_fds[1], 1);
// 		return (1);
// 	}
// 	else if (ast->right)
// 	{
// 		dup2(pipe_fds[0], 0);

// 	}
// }