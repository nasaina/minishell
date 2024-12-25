/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:19:54 by maandria          #+#    #+#             */
/*   Updated: 2024/12/25 13:11:38 by maandria         ###   ########.fr       */
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
