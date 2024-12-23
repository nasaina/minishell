/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 18:05:14 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/24 17:40:05 by nandrian         ###   ########.fr       */
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
	*str = NULL;
	*str = ft_readline();
	if (!*str)
	{
		printf("exit\n");
		unlink("/tmp/.ms_status");
		free_env(env);
		exit(0);
	}
	if (is_error(*str) || is_void(*str))
		return (1);
	return (0);
}

int	check_file(t_expander *expander)
{
	t_expander *tmp;

	tmp = expander;
	while (tmp)
	{
		if (tmp->type != WORD && tmp->type != PIPE)
		{
			tmp = tmp->next;
			if (tmp && tmp->cmd[0] == 0)
				return (1);
		}
		if (!tmp)
			break ;
		tmp = tmp->next;
	}
	return (0);
}

int	redir_syntax(t_chunk *chunks)
{
	t_chunk *tmp;

	tmp = chunks;
	while (tmp)
	{
		if (tmp->type != WORD && tmp->type != PIPE)
		{
			tmp = tmp->next;
			if (tmp && tmp->type != WORD)
			{
				ft_putstr_fd("minshell :syntax error\n", 2);
				ms_writestatus(2);
				free_chunks(chunks);
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int	heredoc_start(char *str, t_chunk *chunks, t_env *env)
{
	int	heredoc_status;

	if (one_hd(str))
	{
		heredoc_status = heredoc_built(str, env, chunks);
		ms_writestatus(heredoc_status);
		if (heredoc_status)
		{
			free_chunks(chunks);
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

void	run_shell(t_expander *expander, t_ast **ast, char **envp, t_env *env)
{
	pid_t	pid = -1;
	int		status = 0;

	*ast = NULL;
	*ast = parse_args(expander, 1);
	free_expander(expander);
	if ((*ast)->type != AST_PIPE && isbuiltin(*ast))
	{
		int fd_in = dup(STDIN_FILENO);
		int fd_out = dup(STDOUT_FILENO);
		status = ms_builtins(*ast, env, fd_in, fd_out);
		if ((*ast)->cmd->redir)
		{
			if (do_redir(*ast) < 0)
				status = 1;
		}
		dup2(fd_in, STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_in);
		close(fd_out);
	}
	else
	{
		pid = fork();
		if (pid < 0)
			perror("fork");
		else if (pid == 0)
		{
			status = 0;
			status = pipe_check(*ast, env, envp);
			free_ast(*ast);
			free_env(env);
			exit(status);
		}
		else
		{
			signal(SIGINT, SIG_IGN);
			waitpid(pid, &status, 0);
			signal(SIGINT, &global_sigint);
		}
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			status = 128 + WTERMSIG(status);
			if (status != 131)
				ft_putstr_fd("\n", 2);
			else
				ft_putstr_fd("Quit (core dumped)\n", 2);
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
