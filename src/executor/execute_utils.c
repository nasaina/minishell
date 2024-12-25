/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:19:54 by maandria          #+#    #+#             */
/*   Updated: 2024/12/25 16:00:54 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	do_fork(t_ast *ast, t_env *env, char *path)
{
	int	status;

	status = -1;
	if (ast->cmd->args && ast->cmd->args[0])
		status = exec_fork(ast, path, env);
	return (status);
}

int	error_command(t_ast *ast, char *path, char **envp)
{
	struct stat	st;

	if (stat(path, &st) == -1)
		perror("stat");
	if (S_ISDIR(st.st_mode))
		path_error(ast, " :Is a directory\n");
	else
		perror((const char *)(ast->cmd->args[0]));
	free(path);
	free_tab(envp);
	return (126);
}

void	close_fds(int *pipe_fds)
{
	close(pipe_fds[0]);
	close(pipe_fds[1]);
}

int	create_pipe(int *pipe_fds)
{
	if (pipe(pipe_fds) < 0)
	{
		perror("pipe");
		return (1);
	}
	return (0);
}

int	create_fork(pid_t *pid, char *str)
{
	*pid = fork();
	if (*pid < 0)
	{
		perror(str);
		return (1);
	}
	return (0);
}

int	wait_children(pid_t pid_left, pid_t pid_right, int *pipe_fds)
{
	int	status_left;
	int	status;

	status = -1;
	close_fds(pipe_fds);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid_left, &status_left, 0);
	waitpid(pid_right, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	if (WIFSIGNALED(status_left))
		ft_putstr_fd("\n", 1);
	return (status);
}
