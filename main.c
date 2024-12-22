#include <minishell.h>

void	start_signal(int ac, char **av, char **env)
{
	ignore_args(ac, av, env);
	signal(SIGINT, &handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

t_env	*get_t_env(t_env *env)
{
	static t_env	*data = NULL;

	if (env == NULL)
		return (data);
	data = env;
	return (data);
}

int	main(int ac, char **av, char **envp)
{
	char	*str;
	int			heredoc_status;
	t_chunk	*chunks;
	t_env	*env = NULL;
	t_expander	*expander;
	t_ast		*ast;

	env = ms_envcpy(envp);
	start_signal(ac, av, envp);
	ms_readhistory();
	while (1)
	{
		str = NULL;
		str = ft_readline();
		if (!str)
		{
			printf("exit\n");
			unlink(".ms_status");
			free_env(env);
			exit(0);
		}
		if (is_error(str) || is_void(str))
			continue ;
		if (one_hd(str))
		{
			heredoc_status = heredoc_built(str, env);
			ms_writestatus(heredoc_status);
			if (heredoc_status)
				continue ;
		}
		chunks = NULL;
		chunks = lexing(str);
		free(str);
		expander = NULL;
		expander = expand_str(chunks, env);
		free_chunks(chunks);
		if (expander)
		{
			if (handle_exit(expander, env))
			{
				ms_writestatus(1);
				continue ;
			}
			ast = NULL;
			ast = parse_args(expander, 1);
			free_expander(expander);
			pipe_check(ast, env, envp);
			if (ast)
				free_ast(ast);
		}
		else
			continue ;
	}
	free_env(env);
}
