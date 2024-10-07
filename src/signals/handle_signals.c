/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:31:27 by maandria          #+#    #+#             */
/*   Updated: 2024/10/07 16:02:47 by nandrian         ###   ########.fr       */
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
	(void)sig;
	return ;
}

void	handle_sigquit(int sig)
{
	(void)sig;
}

void	ft_exit(char **str)
{
	int		index;
	int		status;

	index = 0;
	while (str[index])
		index++;
	index --;
	if (index > 1)
	{
		free_split(str);
		printf("exit : too many arguments");
	}
	else if (index == 1)
	{
		status = ft_atoi(str[index]);
		free_split(str);
		exit (status);
	}
}

int	handle_eof(char *str)
{
	char	**take_set;
	int		index;

	index = 0;
	if (str == NULL || !ft_strncmp(str, "exit", 5))
	{
		printf("exit\n");
		exit (0);
	}
	else if (ft_strncmp(str, "exit", 4) == 0 && str[4] == 32)
	{
		take_set = ft_split(str, ' ');
		printf("exit\n");
		if (!table_isnum(take_set))
		{
			printf ("exit : numeric argument required\n");
			free_split(take_set);
			exit (2);
		}
		ft_exit(take_set);
	}
	return (0);
}
