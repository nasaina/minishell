/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 07:15:18 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/13 12:57:44 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_input(char **args, int i, char *name)
{
	if (is_invalidname(name))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(args[i], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	if (double_input(args, i, name))
		return (1);
	return (0);
}
