/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:38:26 by nandrian          #+#    #+#             */
/*   Updated: 2024/09/16 12:41:23 by nandrian         ###   ########.fr       */
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
			printf("%d : %s\n", is_variable(args->str), args->str);
			args = args->next;
		}
	}
	return (0);
}
