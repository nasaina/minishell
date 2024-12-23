/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:51:47 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/24 17:36:08 by nandrian         ###   ########.fr       */
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
	if (ast->cmd->args[0][0] == '.')
		path = check_access(ast);
	else
		path = check_path(path_list(env), ast);
	return (path);
}

int	exec_fork(t_ast *ast, char *path, t_env *env)
{
	char	**envp;
	int		status;
	struct	stat st;

	status = -1;
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
	free(envp);
	return (0);
}

int	exec_cmd(t_ast *ast, t_env *env)
{
	int		status = -1;
	char	*path;

	path = NULL;
	if (ast->cmd->args && ast->cmd->args[0] && !ast->cmd->args[0][0])
	{
		printf("minishell : : command not found\n");
		return (127);
	}
	if (ast->cmd->args && ast->cmd->args[0])
		path = take_path(ast, env);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	status = do_fork(ast, env, path);
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
		{
			if (do_redir(ast) < 0)
				return (1);
		}
		status = ms_builtins(ast, env, fd_in, fd_out);
		dup2(fd_in, STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_in);
		close(fd_out);
	}
	else
		status = exec_cmd(ast, env);
	return (status);
}
