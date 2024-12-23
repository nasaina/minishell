/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 18:05:14 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/23 13:31:29 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	start_signal(int ac, char **av, char **env)
{
	ignore_args(ac, av, env);
	signal(SIGINT, &global_sigint);
	signal(SIGQUIT, SIG_IGN);
}

int	read_input(char **str, t_env *env)
{
	int	heredoc_status;

	*str = NULL;
	*str = ft_readline();
	if (!*str)
	{
		printf("exit\n");
		unlink(".ms_status");
		free_env(env);
		exit(0);
	}
	if (is_error(*str) || is_void(*str))
		return (1);
	if (one_hd(*str))
	{
		heredoc_status = heredoc_built(*str, env);
		if (heredoc_status == -2)
		{
			ms_writestatus(0);
			return (1);
		}
		else
		{
			ms_writestatus(heredoc_status);
			if (heredoc_status != 0)
				return (1);
		}
	}
	return (0);
}

t_expander	*init_expander(char *str, t_env *env)
{
	t_chunk		*chunks;
	t_expander	*expander;

	chunks = NULL;
	chunks = lexing(str);
	free(str);
	expander = NULL;
	expander = expand_str(chunks, env);
	free_chunks(chunks);
	if (handle_exit(expander, env))
	{
		ms_writestatus(1);
		return (NULL);
	}
	return (expander);
}

void	run_shell(t_expander *expander, t_ast **ast, char **envp, t_env *env)
{
	*ast = NULL;
	*ast = parse_args(expander, 1);
	free_expander(expander);
	pipe_check(*ast, env, envp);
	if (*ast)
		free_ast(*ast);
}

int	main(int ac, char **av, char **envp)
{
	char		*str;
	t_env		*env;
	t_expander	*expander;
	t_ast		*ast;

	env = NULL;
	env = ms_envcpy(envp);
	start_signal(ac, av, envp);
	ms_readhistory();
	while (1)
	{
		if (read_input(&str, env))
			continue ;
		expander = init_expander(str, env);
		if (expander)
			run_shell(expander, &ast, envp, env);
		else
			continue ;
	}
	free_env(env);
}
