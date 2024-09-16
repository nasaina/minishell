/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:38:26 by nandrian          #+#    #+#             */
/*   Updated: 2024/09/16 13:36:34 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_chunk	*args;
	(void)argc;
	(void)argv;
	(void)envp;

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
		// if (is_variable(str))
		// 	printf("%s\n", get_variable(str));
		// else
		// 	printf("%s\n", str);
		printf("%s\n", getenv(get_variable(str)));
		// args = lexing(args, str);
		// while (args)
		// {
		// 	printf("%d : %s\n", is_variable(args->str), args->str);
		// 	args = args->next;
		// }
	}
	return (0);
}
