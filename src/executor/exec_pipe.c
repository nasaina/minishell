/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 13:29:57 by maandria          #+#    #+#             */
/*   Updated: 2024/12/04 13:29:56 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	pipe_check(t_ast *ast, t_export *export, char **env)
{
	if (ast->type == 1)
	{
		exec_pipe(ast, export, env);
	}
	else
		check_cmd(ast, export, env);
}

void	exec_pipe(t_ast *ast, t_export *export, char **env)
{
	pid_t	pid_left;
	pid_t	pid_right;
	int		status;
	int		pipe_fds[2];

	pipe(pipe_fds);
	pid_left = fork();
	if (pid_left < 0)
		perror("fork");
	else if (pid_left == 0)
	{
		if (ast->left)
			exec_pipe_left(ast->left, export, env, pipe_fds);
	}
	else
	{
		pid_right = fork();
		 if (pid_right == 0)
		{ 
			if (ast->right)
				exec_pipe_right(ast->right, export, env, pipe_fds);
		}
		waitpid(pid_left, &status, 0);
	}
}
void	exec_pipe_left(t_ast *ast, t_export *export, char **env, int *pipe_fds)
{
	close(pipe_fds[0]);
	dup2(pipe_fds[1], 1);
	pipe_check(ast, export, env);
	close(pipe_fds[1]);
	exit(EXIT_FAILURE);
}

void	exec_pipe_right(t_ast *ast, t_export *export, char **env, int *pipe_fds)
{
	close(pipe_fds[1]);
	dup2(pipe_fds[0], 0);
	pipe_check(ast, export, env);
	close(pipe_fds[0]);
	exit (EXIT_FAILURE);
}