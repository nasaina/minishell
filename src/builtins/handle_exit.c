/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:17:19 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/19 16:52:03 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_exit2(t_expander *expander, t_export *export)
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
		free_export(export);
		exit(status);
	}
	return (0);
}

int	handle_exit(t_expander *expander, t_export *export)
{
	if (!ft_strcmp(expander->cmd, "exit") && !expander->next)
	{
		free_export(export);
		free_expander(expander);
		printf("exit\n");
		unlink(".ms_status");
		exit(0);
	}
	else if (!ft_strcmp(expander->cmd, "exit") && expander->next)
	{
		if (!str_isnum(expander->next->cmd))
		{
			free_export(export);
			printf("exit\n");
			ft_putstr_fd("exit : numeric argument required\n", 2);
			free_expander(expander);
			unlink(".ms_status");
			exit(2);
		}
		if (ft_exit2(expander, export))
			return (1);
	}
	return (0);
}
