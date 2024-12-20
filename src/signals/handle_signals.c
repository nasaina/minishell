/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:31:27 by maandria          #+#    #+#             */
/*   Updated: 2024/12/20 07:49:29 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	handle_sigint(int sig)
{
	t_heredoc	*heredoc;

	if (sig == SIGINT)
	{
		printf("\n");
		heredoc = get_here_data(NULL);
		close(heredoc->fd);
		free_heredoc_data(heredoc);
		exit(130);
	}
}

void	handle_sigquit(int sig)
{
	if (sig == SIGQUIT)
		exit(131);
}
