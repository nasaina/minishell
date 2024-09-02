/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:50:27 by nandrian          #+#    #+#             */
/*   Updated: 2024/09/02 17:02:43 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int ac, char **av)
{
	char *str;
	char **split;

	if (ac == 5)
	{
		str = get_all_args(ac, av);
		split = split_arg(str);
		printf("%s\n", split[TEXT]);
	}
	return (0);
}