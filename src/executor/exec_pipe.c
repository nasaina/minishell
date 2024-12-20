/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 13:29:57 by maandria          #+#    #+#             */
/*   Updated: 2024/12/20 08:03:27 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	pipe_check(t_ast *ast, t_env *env, char **envp)
{
	int	status;

	if (ast->type == 1)
		status = exec_pipe(ast, env, envp);
	else
		status = check_cmd(ast, env, envp);
	ms_writestatus(status);
	return (status);
}

int	exec_pipe(t_ast *ast, t_env *env, char **envp)
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
		exec_pipe_left(ast->left, env, envp, pipe_fds);
	pid_right = fork();
	if (pid_right < 0)
		perror("fork");
	else if (pid_right == 0)
	{
			status = exec_pipe_right(ast->right, env, envp, pipe_fds);
			exit(EXIT_FAILURE);
	}
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, &status, 0);
	if ( WIFEXITED(status))
        status = WEXITSTATUS(status);
	return (status);
}

void	exec_pipe_left(t_ast *ast, t_env *env, char **envp, int *pipe_fds)
{
	if (ast)
	{
		close(pipe_fds[0]);
		dup2(pipe_fds[1], 1);
		close(pipe_fds[1]);
		pipe_check(ast, env, envp);
	}
	exit(EXIT_SUCCESS);
}

int	exec_pipe_right(t_ast *ast, t_env *env, char **envp, int *pipe_fds)
{
	int		status = -1;

	if (ast)
	{
		close(pipe_fds[1]);
		dup2(pipe_fds[0], 0);
		close(pipe_fds[0]);
		status = pipe_check(ast, env, envp);
		
		exit (status);
	}
	return (EXIT_FAILURE);
}
