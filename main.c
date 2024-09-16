/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:38:26 by nandrian          #+#    #+#             */
/*   Updated: 2024/09/16 10:51:15 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(void)
{
	char	*str;
	t_chunk	*args;

	args = NULL;
	while (1)
	{
		str = readline(">  ");
		add_history(str);
		if (!check_redirection(str))
		{
			free(str);
			continue ;
		}
		args = lexing(args, str);
		while (args)
		{
			printf("%u %s\n", args->type, args->str);
			args = args->next;
		}
	}
	return (0);
}
