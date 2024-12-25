/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 16:11:54 by maandria          #+#    #+#             */
/*   Updated: 2024/12/25 17:02:15 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

int	wait_children(pid_t pid_left, pid_t pid_right, int *status, int *status_left)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid_left, status_left, 0);
	waitpid(pid_right, status, 0);
	if (WIFEXITED(*status))
		*status = WEXITSTATUS(*status);
	if (WIFSIGNALED(*status_left))
		ft_putstr_fd("\n", 1);
	return (*status);
}
