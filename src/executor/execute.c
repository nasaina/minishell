/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:51:47 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/22 15:06:51 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	isbuiltin(t_ast *ast)
{
	int			i;
	char	**builtins;

	if (!ast)
		return (0);
	builtins = init_builtins(); 
	i = 0;
	while (builtins[i])
	{
		if (ft_strcmp(ast->cmd->args[0], (char *)builtins[i]) == 0)
			return (1);
		else
			i++;
	}
	return (0);
}

char	*take_path(t_ast *ast, t_env *env)
{
	char	*path;
	
	path = NULL;
	if (is_command(ast))
		path = check_access(ast);
	else
		path = check_path(path_list(env), ast);
	return (path);
}

int	exec_fork(t_ast *ast, char *path, t_env *env)
{
	char	**envp;
	int		status;

	status = -1;
	envp = take_env(env);
	if (!path)
	{
		free_ast(ast);
		free_tab(envp);
		free_env(env);
		return (127);
	}
	if (execve(path, ast->cmd->args, envp) == -1)
	{
		perror((const char *)(ast->cmd->args[0]));
		free_ast(ast);
		free(path);
		free_tab(envp);
		free_env(env);
		return (126);
	}
	return (0);
}

int	exec_cmd(t_ast *ast, t_env *env)
{
	int		status = -1;
	char	*path;
	pid_t	pid;

	path = NULL;
	if (ast->cmd->args && ast->cmd->args[0])
		path = take_path(ast, env);
	pid = fork();
	if (pid < 0)
		perror("fork");
	else if (pid == 0)
	{
		status = do_fork(ast, env, path);
		free(path);
		exit (EXIT_FAILURE);
	}
	else
	{
		free(path);
		waitpid(pid, &status, 0);
	}
	if ( WIFEXITED(status) )
        status = WEXITSTATUS(status);
	return (status);
}

int	check_cmd(t_ast *ast, t_env *env)
{
	int	fd_in;
	int	fd_out;
	int	status = -1;

	if (isbuiltin(ast))
	{
		fd_in = dup(STDIN_FILENO);
		fd_out = dup(STDOUT_FILENO);
		if (ast->cmd->redir)
			do_redir(ast);
		status = ms_builtins(ast, env);
		dup2(fd_in, STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_in);
		close(fd_out);
	}
	else
		status = exec_cmd(ast, env);
	return (status);
}
