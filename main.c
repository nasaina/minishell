/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:38:26 by nandrian          #+#    #+#             */
/*   Updated: 2024/11/11 16:42:48 by nandrian         ###   ########.fr       */
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
	else if (ast->type == AST_CMD)
	{
		int i = 0;
		while (ast->cmd->args[i])
		{
			printf("type %d : ", ast->type);
			printf("%s ", ast->cmd->args[i]);
			i++;
		}
		write(1, "\n", 2);
		printf("REDIR\n");
		while (ast->cmd->redir != NULL)
		{
			printf("*********type %d : %s\n", ast->cmd->redir->type, ast->cmd->redir->file);
			ast->cmd->redir = ast->cmd->redir->next;
		}
	}
	print_ast(ast->left);
	print_ast(ast->right);
}

void	prinexp(t_expander *expander)
{
	if (!expander)
		return ;
	while (expander)
	{
		printf("%s\n", expander->cmd);
		expander = expander->next;
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char	*str = NULL;
	t_chunk	*chunks = NULL;
	t_export	*export = NULL;
	t_expander	*expander = NULL;
	t_ast		*ast = NULL;

	export = ms_envcpy(env);
	start_signal(ac, av, env);
	while (1)
	{
		str = ft_readline(str);
		if (is_error(str))
			continue ;
		chunks = lexing(str);
		expander = expand_str(chunks, export);
		ast = parse_args(expander);
		check_cmd(ast, export, expander, str, env);
		free_expander(expander);
		print_ast(ast);
		printf("\n");
		free(str);
	}
	free_export(export);
}
