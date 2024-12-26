/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 18:05:14 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/26 12:10:23 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_expander	*init_expander(char *str, t_env *env)
{
	t_chunk		*chunks;
	t_expander	*expander;

	chunks = NULL;
	chunks = lexing(str);
	if (redir_syntax(chunks))
		return (NULL);
	if (heredoc_start(str, chunks, env))
		return (NULL);
	free(str);
	expander = NULL;
	expander = expand_str(chunks, env);
	if (expander && check_file(expander))
	{
		ft_putstr_fd("minishell: : No such file or directory\n", 2);
		ms_writestatus(1);
		free_expander(expander);
		return (NULL);
	}
	return (expander);
}

int	do_builtins(t_ast *ast, t_env *env)
{
	int	fd_in;
	int	fd_out;
	int	status;

	status = 0;
	fd_in = dup(STDIN_FILENO);
	fd_out = dup(STDOUT_FILENO);
	if (ast->cmd->redir)
	{
		if (do_redir(ast) < 0)
		{
			dup2(fd_in, STDIN_FILENO);
			dup2(fd_out, STDOUT_FILENO);
			close(fd_in);
			close(fd_out);
			return (1);
		}
	}
	status = ms_builtins(ast, env, fd_in, fd_out);
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_in);
	close(fd_out);
	return (status);
}

int	child_process(t_ast *ast, char **envp, t_env *env)
{
	pid_t	pid;
	int		status;

	pid = -1;
	status = 0;
	pid = fork();
	if (pid < 0)
		perror("fork");
	else if (pid == 0)
	{
		status = 0;
		status = pipe_check(ast, env, envp);
		free_ast(ast);
		free_env(env);
		exit(status);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		signal(SIGINT, &global_sigint);
	}
	return (status);
}

void	run_shell(t_expander *expander, t_ast **ast, char **envp, t_env *env)
{
	int		status;

	*ast = NULL;
	*ast = parse_args(expander, 1);
	free_expander(expander);
	status = 0;
	if ((*ast)->type != AST_PIPE && isbuiltin(*ast))
		status = do_builtins(*ast, env);
	else
	{
		status = child_process(*ast, envp, env);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			status = 128 + WTERMSIG(status);
			if (status != 131)
				ft_putstr_fd("\n", 1);
			else
				ft_putstr_fd("Quit (core dumped)\n", 1);
		}
	}
	ms_writestatus(status);
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
	(void)ac;
	(void)av;
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
