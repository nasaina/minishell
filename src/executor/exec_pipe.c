/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 13:29:57 by maandria          #+#    #+#             */
/*   Updated: 2024/12/24 14:39:28 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	pipe_check(t_ast *ast, t_env *env, char **envp)
{
	int	status;

	if (ast->type == 1)
		status = exec_pipe(ast, env, envp);
	else
		status = check_cmd(ast, env);
	return (status);
}

int	exec_pipe(t_ast *ast, t_env *env, char **envp)
{
	pid_t	pid_left;
	pid_t	pid_right;
	int		status;
	int		status_left;
	int		pipe_fds[2];

	status = -1;
	status_left = -1;
	if (pipe(pipe_fds) < 0)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid_left = fork();
	if (pid_left < 0)
		perror("fork(left)");
	else if (pid_left == 0)
		status_left = exec_pipe_left(ast->left, env, envp, pipe_fds);
	else
	{
		pid_right = fork();
		if (pid_right < 0)
			perror("fork(right)");
		else if (pid_right == 0)
		{
			status = exec_pipe_right(ast->right, env, envp, pipe_fds);
		}
		else
		{
			close(pipe_fds[0]);
			close(pipe_fds[1]);
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			waitpid(pid_left, &status_left, 0);
			waitpid(pid_right, &status, 0);
			if (WIFEXITED(status))
				status = WEXITSTATUS(status);
			if (WIFSIGNALED(status_left))
				ft_putstr_fd("\n", 2);
		}
	}
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	return (status);
}

int	exec_pipe_left(t_ast *ast, t_env *env, char **envp, int *pipe_fds)
{
	int status;

	if (ast)
	{
		if (dup2(pipe_fds[1], 1) == -1)
		{
			perror("dup2(left)");
			free_ast(ast);
			exit(EXIT_FAILURE);
		}
		status = pipe_check(ast, env, envp);
		// close(pipe_fds[0]);
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
