#include <minishell.h>

void	start_signal(int ac, char **av, char **env)
{
	ignore_args(ac, av, env);
	signal(SIGINT, &handle_sigint);
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

t_heredoc	*get_here_data(t_heredoc *heredoc)
{
	static t_heredoc	*data = NULL;

	if (heredoc == NULL)
		return (data);
	data = heredoc;
	return (data);
}

t_env	*get_t_env(t_env *env)
{
	static t_env	*data = NULL;

	if (env == NULL)
		return (data);
	data = env;
	return (data);
}

void	init_heredoc(t_env *env, t_heredoc **heredoc)
{
	*heredoc = ft_calloc(sizeof(t_heredoc), 1);
	if (!(*heredoc))
		return ;
	(*heredoc)->env = env;
	(*heredoc)->file = NULL;
	(*heredoc)->fd = 0;
}

void	do_heredoc(char *str, t_heredoc *data, int i)
{
	t_redir		*tmp;

	data->lst = expand_hdoc(str);
	free(str);
	tmp = data->lst;
	signal(SIGINT, &handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			i++;
			tmp = tmp->next;
		}
		data->file = join_free("/tmp/.hd_tmp", ft_itoa(i), 1);
		data->name = ignore_quote(tmp->file);
		get_here_data(data);
		data->fd = get_input(data, tmp);
		close(data->fd);
		free(data->file);
		tmp = tmp->next;
	}
	free_redir(data->lst);
}

int	check_hdstatus(int status, t_heredoc *data)
{
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 130)
		{
			free(data);
			return (130);
		}
		else
		{
			free(data);
			return (0);
		}
	}
	return (0);
}

int	heredoc_built(char *str, t_env *env)
{
	int			i;
	int			status;
	pid_t		hd_pid;
	t_heredoc	*data;

	data = NULL;
	init_heredoc(env, &data);
	hd_pid = fork();
	i = 1;
	if (hd_pid < 0)
		perror("fork");
	else if (hd_pid == 0)
	{
		do_heredoc(str, data, i);
		free_env(env);
		free(data);
		exit(0);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(hd_pid, &status, 0);
	return (check_hdstatus(status, data));
}

int	one_hd(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<')
			return (1);
		i++;
	}
	return (0);
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
