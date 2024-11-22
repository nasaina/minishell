/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:41:49 by nandrian          #+#    #+#             */
/*   Updated: 2024/11/22 16:08:14 by maandria         ###   ########.fr       */
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
	if (str != NULL && str[0] != '\0')
		add_history(str);
	handle_eof(str);
	return (str);
}

int	is_void(char *str)
{
	int	i;

	i = 0;
	if (str != NULL && str[i] == '\0')
	{
		free(str);
		return (1);
	}
	else if (str != NULL && str[i] == 32)
	{
		while (str[i] == 32)
			i++;
		if (str[i] == '\0')
			return (1);
	}
	return (0);
}