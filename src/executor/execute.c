/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:51:47 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/12 12:42:08 by nandrian         ###   ########.fr       */
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

char	*take_path(t_ast *ast, char **env)
{
	char	*path;

		if (ft_strchr(ast->cmd->args[0], '/'))
			path = check_access(ast);
		else
			path = check_path(path_list(env), ast);
	return (path);
}

void	exec_cmd(t_ast *ast, char **env)
{
	int		status;
	char	*path;
	pid_t	pid;

	path = NULL;
	if (ast->cmd->args)
		path = take_path(ast, env);
	pid = fork();
	if (pid < 0)
		perror("fork");
	else if (pid == 0)
	{
		if (ast->cmd->redir)
			do_redir(ast);
		if (execve(path, &ast->cmd->args[0], env) == -1)
		{
			if (path == NULL || &ast->cmd->args[0] == NULL)
				exit (EXIT_FAILURE);
			perror((const char *)(ast->cmd->args[0]));
		}
		exit (EXIT_FAILURE);
	}
	else
		waitpid(pid, &status, 0);
}

void	check_cmd(t_ast *ast, t_export *export, char **env)
{
	int	fd_in;
	int	fd_out;

	if (isbuiltin(ast))
	{
		fd_in = dup(STDIN_FILENO);
		fd_out = dup(STDOUT_FILENO);
		if (ast->cmd->redir)
			do_redir(ast);
		ms_builtins(ast, export);
		dup2(fd_in, STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_in);
		close(fd_out);
	}
	else
		exec_cmd(ast, env);
}
