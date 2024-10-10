/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:51:47 by nandrian          #+#    #+#             */
/*   Updated: 2024/10/10 20:33:57 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	isbuiltin(t_cmd *cmd)
{
	char	**builtins;
	int	i;

	builtins = {"echo", "cd", "pwd", "export", "env", "unset", "exit", NULL}
	i = 0;
	while (builtins[i])
	{
		if (ft_strcmp(cmd->args[0], builtins[i]) == 0)
			return (1);
		else
			i++;
	}
	return (0);
}

void	exec_cmd(t_cmd *cmd)
{
	pid_t	pid;
	int	status;

	pid = fork();
	if (pid < 0)
		perror("fork");
	else if (pid == 0)
	{
		if (execve(cmd->args[0], cmd->args, NULL ) == -1)
			perror("execve");
		exit (EXIT_FAILURE);
	}
	else
		waitpid(pid, &status, 0);
}

void	check_cmd(t_cmd *cmd, t_export *export, t_chunk *chunks, char *str, char **env)
{
	if (!isbuiltin(cmd))
		exec_cmd(cmd);
	else
		ms_builtins(export, chunks, str, env);
}
