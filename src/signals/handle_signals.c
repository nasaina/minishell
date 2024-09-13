/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:31:27 by maandria          #+#    #+#             */
/*   Updated: 2024/09/13 17:09:29 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handle_sigint(int sig)
{
	(void)sig;
	printf("^C");
	exit(0);
}

void	handle_sigquit(int sig)
{
	(void)sig;
	printf("Signal SIGQUIT recu");
}

int		handle_eof(char *str)
{
	if (str == NULL || !ft_strncmp(str, "exit", 6))
	{
		printf("exit\n");
		return (1);
	}
	return (0);
}
