/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:38:26 by nandrian          #+#    #+#             */
/*   Updated: 2024/10/07 15:59:40 by nandrian         ###   ########.fr       */
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
	char	*str;
	t_chunk	*args;
	t_ast	*ast;

	args = NULL;
	str = NULL;
	ast = NULL;
	start_signal(ac, av, env);
	while (1)
	{
		str = ft_readline(str);
		if (is_error(str))
			continue ;
		args = lexing(args, str);
		while (args)
		{
			if (ft_strncmp(args->str, "pwd", 4) == 0)
				ms_pwd();
			printf("%s", expander(args->str, env));
			args = args->next;
		}
		// printf("%d\n", count_chunks(args));
		// ast = parse_args(args);
		// print_ast(ast);
		printf("\n");
	}
	free_chunks(args);
	return (0);
}
