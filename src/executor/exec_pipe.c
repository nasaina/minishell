/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 13:29:57 by maandria          #+#    #+#             */
/*   Updated: 2024/12/10 12:59:49 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	pipe_check(t_ast *ast, t_export *export, char **env)
{
	if (ast->type == 1)
			exec_pipe(ast, export, env);
	else
		check_cmd(ast, export, env);
}

void	exec_pipe(t_ast *ast, t_export *export, char **env)
{
	pid_t	pid_left;
	pid_t	pid_right;
	int		status;
	int		pipe_fds[2];

	if (pipe(pipe_fds) < 0)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid_left = fork();
	if (pid_left < 0)
		perror("fork");
	else if (pid_left == 0)
		exec_pipe_left(ast->left, export, env, pipe_fds);
	pid_right = fork();
	if (pid_right < 0)
		perror("fork");
	else if (pid_right == 0) 
			exec_pipe_right(ast->right, export, env, pipe_fds);
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	waitpid(pid_left, &status, 0);
	waitpid(pid_right, &status, 0);
}

void	exec_pipe_left(t_ast *ast, t_export *export, char **env, int *pipe_fds)
{
	if (ast)
	{
		close(pipe_fds[0]);
		dup2(pipe_fds[1], 1);
		close(pipe_fds[1]);
		pipe_check(ast, export, env);
	}
	exit(EXIT_SUCCESS);
}

void	exec_pipe_right(t_ast *ast, t_export *export, char **env, int *pipe_fds)
{
	if (ast)
	{
		close(pipe_fds[1]);
		dup2(pipe_fds[0], 0);
		close(pipe_fds[0]);
		pipe_check(ast, export, env);
	}
	exit (EXIT_SUCCESS);
}
