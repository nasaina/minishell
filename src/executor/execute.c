/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:51:47 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/26 12:15:20 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	isbuiltin(t_ast *ast)
{
	int		i;
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

char	*take_path(t_ast *ast, t_env *env, int *status)
{
	char	*path;

	path = NULL;
	if (ast->cmd->args[0][0] == '.' || ast->cmd->args[0][0] == '/')
		path = check_access(ast);
	else
		path = check_path(path_list(env), ast, status);
	return (path);
}

int	exec_fork(t_ast *ast, char *path, t_env *env)
{
	char		**envp;

	envp = take_env(env);
	if (ast->cmd->redir)
	{
		if (do_redir(ast) < 0)
		{
			if (path)
				free(path);
			free_tab(envp);
			return (1);
		}
	}
	if (!path)
	{
		free_tab(envp);
		return (127);
	}
	if (execve(path, ast->cmd->args, envp) == -1)
	{
		return (error_command(ast, path, envp));
	}
	free(envp);
	return (0);
}

int	exec_cmd(t_ast *ast, t_env *env)
{
	int		status;
	char	*path;

	path = NULL;
	status = -1;
	if (ast->cmd->args && ast->cmd->args[0] && !ast->cmd->args[0][0])
	{
		ft_putendl_fd("minishell : : command not found", 2);
		return (127);
	}
	if (ast->cmd->args && ast->cmd->args[0])
		path = take_path(ast, env, &status);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	if (status == 126)
		return (status);
	status = do_fork(ast, env, path);
	return (status);
}

int	check_cmd(t_ast *ast, t_env *env)
{
	int	fd_in;
	int	fd_out;
	int	status;

	status = -1;
	if (isbuiltin(ast))
	{
		fd_in = dup(STDIN_FILENO);
		fd_out = dup(STDOUT_FILENO);
		if (ast->cmd->redir)
		{
			if (do_redir(ast) < 0)
				return (1);
		}
		status = ms_builtins_pipe(ast, env);
		dup2(fd_in, STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_in);
		close(fd_out);
	}
	else
		status = exec_cmd(ast, env);
	return (status);
}
