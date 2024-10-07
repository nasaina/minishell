/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:41:49 by nandrian          #+#    #+#             */
/*   Updated: 2024/10/07 15:20:50 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_error(char *str)
{
	if (!check_redirection(str))
	{
		free(str);
		return (1);
	}
	return (0);
}

void	ignore_args(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
}

char	*ft_readline(char *str)
{
	str = readline(">  ");
	add_history(str);
	handle_eof(str);
	return (str);
}
