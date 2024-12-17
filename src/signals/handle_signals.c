/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:31:27 by maandria          #+#    #+#             */
/*   Updated: 2024/12/17 11:15:57 by nandrian         ###   ########.fr       */
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
		printf("exit : too many arguments\n");
	}
	else if (index == 1)
	{
		status = ft_atoi(str[index]);
		free_split(str);
		exit (status);
	}
}

int	handle_eof(char *str, t_export *export)
{
	char	**take_set;

	if (str == NULL || !ft_strncmp(str, "exit", 5))
	{
		free_export(export);
		printf("exit\n");
		exit (0);
	}
	else if (ft_strncmp(str, "exit", 4) == 0 && str[4] == 32)
	{
		free_export(export);
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
