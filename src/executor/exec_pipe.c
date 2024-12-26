/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 13:29:57 by maandria          #+#    #+#             */
/*   Updated: 2024/12/26 09:05:24 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	pipe_check(t_ast *ast, t_env *env, char **envp)
{
	int	status;

	status = -1;
	if (ast->type == 1)
		status = exec_pipe(ast, env, envp, status);
	else
		status = check_cmd(ast, env);
	return (status);
}

int	exec_pipe(t_ast *ast, t_env *env, char **envp, int status)
{
	pid_t	pid_l;
	pid_t	pid_right;
	int		status_left;
	int		pipe_fds[2];

	status_left = -1;
	if (create_pipe(pipe_fds) || create_fork(&pid_l, "fork (left)"))
		return (EXIT_FAILURE);
	if (pid_l == 0)
		status_left = exec_pipe_left(ast->left, env, envp, pipe_fds);
	else
	{
		if (create_fork(&pid_right, "fork (right)"))
			return (EXIT_FAILURE);
		if (pid_right == 0)
			status = exec_pipe_right(ast->right, env, envp, pipe_fds);
		else
		{
			close_fds(pipe_fds);
			if (wait_children(pid_l, pid_right, &status, &status_left) >= 0)
				return (wait_children(pid_l, pid_right, &status, &status_left));
		}
	}
	close_fds(pipe_fds);
	return (status);
}

int	exec_pipe_left(t_ast *ast, t_env *env, char **envp, int *pipe_fds)
{
	int	status;

	if (ast)
	{
		if (dup2(pipe_fds[1], 1) == -1)
		{
			perror("dup2(left)");
			free_ast(ast);
			exit(EXIT_FAILURE);
		}
		status = pipe_check(ast, env, envp);
		close(pipe_fds[1]);
		return (status);
	}
	return (EXIT_FAILURE);
}

int	exec_pipe_right(t_ast *ast, t_env *env, char **envp, int *pipe_fds)
{
	int		status;

	status = -1;
	if (ast)
	{
		if (dup2(pipe_fds[0], 0))
		{
			perror("dup2(right)");
			return (EXIT_FAILURE);
		}
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		status = pipe_check(ast, env, envp);
		return (status);
	}
	return (EXIT_FAILURE);
}
