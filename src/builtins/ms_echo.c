/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:54:57 by maandria          #+#    #+#             */
/*   Updated: 2024/12/25 16:49:33 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_echoflag(char *str)
{
	int	i;

	i = 1;
	if (str[0] == 45 && str[1] && str[1] == 'n')
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

int	echo_flagonly(char **str)
{
	if (is_echoflag(str[1]) && !str[2])
		return (1);
	return (0);
}

void	echo_monitor(char **str, int i)
{
	if (echo_flagonly(str))
		rl_redisplay();
	else if (is_echoflag(str[i]) && str[i + 1])
	{
		while (str[i] && is_echoflag(str[i]))
			i++;
		while (str[i])
		{
			ft_putstr_fd(str[i], 1);
			i++;
			if (str[i])
				ft_putstr_fd(" ", 1);
		}
	}
	else if (str[i])
	{
		while (str[i])
		{
			ft_putstr_fd(str[i], 1);
			i++;
			if (str[i])
				ft_putstr_fd(" ", 1);
		}
		ft_putendl_fd("", 1);
	}
}

int	ms_echo(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!ft_strncmp(cmd->args[i], "echo", 5))
	{
		i++;
		if (!cmd->args[i])
		{
			ft_putstr_fd("\n", 1);
			return (0);
		}
		echo_monitor(cmd->args, i);
	}
	return (0);
}
