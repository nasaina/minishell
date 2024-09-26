/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:31:27 by maandria          #+#    #+#             */
/*   Updated: 2024/09/23 14:43:20 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handle_sigint(int sig)
{
	(void)sig;
	printf("^C");
}

void	handle_sigquit(int sig)
{
	(void)sig;
	printf("Signal SIGQUIT recu");
}

int	handle_eof(char *str)
{
	if (str == NULL || !ft_strncmp(str, "exit", 6))
	{
		printf("exit\n");
		exit (0);
	}
	return (0);
}
