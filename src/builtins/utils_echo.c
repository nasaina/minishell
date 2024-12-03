/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:54:57 by maandria          #+#    #+#             */
/*   Updated: 2024/11/27 11:29:28 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_echoflag(char *str)
{
	int	i;

	i = 1;
	if (str[0] == 45)
	{
		while (str[i])
		{
			if (str[i] == 110)
				i++;
			else
				return (0);
		}
		return (1);
	}
	return (0);
}

int	echo_flagonly(t_expander *expander)
{
	if (is_echoflag(expander->cmd) && !expander->next)
		return (1);
	else
		return (0);
}

void	echo_monitor(t_expander *expander)
{
	if (echo_flagonly(expander))
		rl_redisplay();
	else if (is_echoflag(expander->cmd) && expander->cmd)
	{
		while (expander && is_echoflag(expander->cmd))
			expander = expander->next;
		while (expander)
			{
				printf("%s", expander->cmd);
				expander = expander->next;
				if (expander)
					printf(" ");
			}
	}
	else if (expander)
	{
		while (expander)
		{
			if (ft_strncmp(expander->cmd, "|", 2) == 0)
				break ;
			printf("%s", expander->cmd);
			expander = expander->next;
			if (expander)
				printf(" ");
		}
		printf("\n");
	}
}

void	ms_echo(t_expander *expander)
{
	if (!ft_strncmp(expander->cmd, "echo", 5))
	{
		expander = expander->next;
		if (!expander)
			return ;
		echo_monitor(expander);
	}
}
