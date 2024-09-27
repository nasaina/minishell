/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:31:27 by maandria          #+#    #+#             */
/*   Updated: 2024/09/27 11:33:29 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handle_sigint(int sig)
{
	(void)sig;
	return ;
}

void	handle_sigquit(int sig)
{
	(void)sig;
	/*printf("Signal SIGQUIT recu");*/
}

int	handle_eof(char *str)
{
	char	**take_set;
	int		index;

	index = 0;
	if (str == NULL || !ft_strncmp(str, "exit", 6))
	{
		printf("exit\n");
		exit (0);
	}
	else if (ft_strncmp(str, "exit",6) > 0)
	{
		take_set = ft_split(str, ' ');
		printf("exit\n");
		while (take_set[index])
			index++;
		index --;
		if (index > 1)
			printf("exit : too many arguments");
		else if (index == 1)
			exit (ft_atoi(take_set[index]));
	}
	return (0);
}
