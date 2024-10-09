/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:38:26 by nandrian          #+#    #+#             */
/*   Updated: 2024/10/09 10:07:22 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	start_signal(int ac, char **av, char **env)
{
	ignore_args(ac, av, env);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	print_ast(t_ast *ast)
{
	if (!ast)
		return;
	if (ast->type == AST_PIPE)
		printf("PIPE\n");
	if (ast->type == AST_COMMAND)
		printf("%s\n", ast->cmd->args[0]);
	print_ast(ast->left);
	print_ast(ast->right);
}

int	main(int ac, char **av, char **env)
{
	char		*str;
	t_chunk		*args;
	t_ast		*ast;
	t_export	*export;

	args = NULL;
	str = NULL;
	ast = NULL;
	export = ms_getenv(env);
	start_signal(ac, av, env);
	while (1)
	{
		str = ft_readline(str);
		if (is_error(str))
			continue ;
		args = lexing(args, str);
		int s = 0;
		while (args)
		{
			ms_builtins(export, args, str, env);
			// printf("%d %s", s, expander(args->str, env));
			s++;
			args = args->next;
		}
		// printf("%d\n", count_chunks(args));
		// ast = parse_args(args);
		// print_ast(ast);
		// printf("\n");
		free_chunks(args);
	}
	return (0);
}
