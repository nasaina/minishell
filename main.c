/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:38:26 by nandrian          #+#    #+#             */
/*   Updated: 2024/09/17 08:37:47 by nandrian         ###   ########.fr       */
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
	// signal(SIGINT, handle_sigint);
	// signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		str = readline(">  ");
		add_history(str);
		handle_eof(str);
		if (!check_redirection(str))
		{
			free(str);
			continue ;
		}
		// if (is_variable(str))
		// 	printf("%s\n", get_variable(str));
		// else
		// 	printf("%s\n", str);
		args = lexing(args, str);
		int i = 0;
		while (args)
		{
			printf("%d %s\n", i++, args->str);
			args = args->next;
		}
	}
	return (0);
}
