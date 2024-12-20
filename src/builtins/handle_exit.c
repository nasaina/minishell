/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:17:19 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/20 07:48:57 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_exit(t_expander *expander, t_env *env)
{
	int			i;
	int			status;
	t_expander	*tmp;

	i = 0;
	tmp = expander;
	while (tmp->next)
	{
		i++;
		tmp = tmp->next;
	}
	if (i > 1)
	{
		free_expander(expander);
		ft_putendl_fd("exit : too many arguments", 2);
		return (1);
	}
	else if (i == 1)
	{
		status = ft_atoi(tmp->cmd);
		free_expander(expander);
		free_env(env);
		exit(status);
	}
	return (0);
}

int	handle_exit(t_expander *expander, t_env *env)
{
	if (!ft_strcmp(expander->cmd, "exit") && !expander->next)
	{
		free_env(env);
		free_expander(expander);
		printf("exit\n");
		unlink(".ms_status");
		exit(0);
	}
	else if (!ft_strcmp(expander->cmd, "exit") && expander->next)
	{
		if (!str_isnum(expander->next->cmd))
		{
			free_env(env);
			printf("exit\n");
			ft_putstr_fd("exit : numeric argument required\n", 2);
			free_expander(expander);
			unlink(".ms_status");
			exit(2);
		}
		if (ft_exit(expander, env))
			return (1);
	}
	return (0);
}
