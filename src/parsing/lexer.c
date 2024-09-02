/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:14:24 by nandrian          #+#    #+#             */
/*   Updated: 2024/09/02 16:52:51 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char *get_all_args(int ac, char **av)
{
	char	*str;
	int 	i;

	i = 1;
	str = NULL;
	while (i < ac)
	{
		str = ft_strjoin(str, av[i]);
		str = ft_strjoin(str, "*");
		i++;
	}
	return (str);
}

char **split_arg(char *args)
{
	char **str;

	str = ft_split(args, '*');
	return (str);
}

int is_command(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalpha(str[i]))
			return (0);
		i++;
	}
	return (1);
}
