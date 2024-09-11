/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:38:26 by nandrian          #+#    #+#             */
/*   Updated: 2024/09/11 16:51:50 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_next(char *str, int i)
{
	while (str[i] == 32 && str[i])
	{
		i += 1;		
	}
	if (!str[i])
		return (0);
	return (1);
}

int	isredirection(char c)
{
	char *str;

	str = "< > >> <<";
	if (ft_strchr(str, c))
		return (1);
	return (0);
}

int	main()
{
	char *str;
	char **split;
	int		i;

	while (1)
	{
		str = readline(">  ");
		split = ft_split(str, ' ');
		i = 0;
		while (str[i])
		{
			if (isredirection(str[i]))
			{
				if ((isredirection(str[i + 1]) && str[i] != str[i + 1]) || !check_next(str, i + 1))
				{
					printf("Syntax error\n");
					break ;
				}
			}
			i++;
		}
		add_history(str);
	}
	return (0);
}
