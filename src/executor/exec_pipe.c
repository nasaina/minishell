/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 13:29:57 by maandria          #+#    #+#             */
/*   Updated: 2024/12/19 16:02:30 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_writestatus(int status)
{
	int		fd;
	char	*str;

	fd = open(".ms_status", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd == -1)
		return ;
	str = ft_itoa(status);
	ft_putstr_fd(str, fd);
	free(str);
	close(fd);
}

int	pipe_check(t_ast *ast, t_export *export, char **env)
{
	int	status;

	if (ast->type == 1)
		status = exec_pipe(ast, export, env);
	else
		status = check_cmd(ast, export, env);
	ms_writestatus(status);
	return (status);
}

int	exec_pipe(t_ast *ast, t_export *export, char **env)
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
	{
			status = exec_pipe_right(ast->right, export, env, pipe_fds);
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

int	exec_pipe_right(t_ast *ast, t_export *export, char **env, int *pipe_fds)
{
	int		status = -1;

	if (ast)
	{
		close(pipe_fds[1]);
		dup2(pipe_fds[0], 0);
		close(pipe_fds[0]);
		status = pipe_check(ast, export, env);
		
		exit (status);
	}
	return (EXIT_FAILURE);
}
