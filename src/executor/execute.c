/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:51:47 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/20 07:36:08 by nandrian         ###   ########.fr       */
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

char	*take_path(t_ast *ast, char **envp)
{
	char	*path;

		if (ft_strchr(ast->cmd->args[0], '/'))
			path = check_access(ast);
		else
			path = check_path(path_list(envp), ast);
	return (path);
}

void	exec_fork(t_ast *ast, char *path, char **envp)
{
	if (execve(path, &ast->cmd->args[0], envp) == -1)
	{
		if (path == NULL || &ast->cmd->args[0] == NULL)
    	{
      		free_ast(ast);
			exit (127);
    	}
		else
		{
			perror((const char *)(ast->cmd->args[0]));
			free_ast(ast);
			exit(126);
		}
	}
}

int	exec_cmd(t_ast *ast, char **envp)
{
	int		status = -1;
	char	*path;
	pid_t	pid;

	path = NULL;
	if (ast->cmd->args && ast->cmd->args[0])
		path = take_path(ast, envp);
	pid = fork();
	if (pid < 0)
		perror("fork");
	else if (pid == 0)
	{
		if (ast->cmd->redir)
			do_redir(ast);
		if (ast->cmd->args && ast->cmd->args[0])
			exec_fork(ast, path, envp);
		exit (EXIT_FAILURE);
	}
	else
		waitpid(pid, &status, 0);
	if ( WIFEXITED(status) )
        status = WEXITSTATUS(status);
	return (status);
}

int	check_cmd(t_ast *ast, t_env *env, char **envp)
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
		status = exec_cmd(ast, envp);
	return (status);
}
