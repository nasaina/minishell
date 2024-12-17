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

int	redir_ok(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (isredirection(str[i]) && str[i] == str[i + 1])
			return (1);
		if (isredirection(str[i]) && !isredirection(str[i + 1]))
			return (1);
		if (str[i] == '<' && str[i + 1] == '>')
			return (0);
		if (isredirection(str[i] && isredirection(str[i + 1])
			&& isredirection(str[i + 2])))
			return (0);
		i++;
	}
	return (0);
}

int	redir_null(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (isredirection(str[i]) && !str[i + 1])
		{
			printf("Syntax error\n");
			free(str);
			return (1);
		}
		i++;
	}
	return (0);
}

t_heredoc	*get_here_data(t_heredoc *heredoc)
{
	static t_heredoc	*data = NULL;

	if (heredoc == NULL)
		return (data);
	data = heredoc;
	return (data);
}


void	init_heredoc(t_export *export, t_heredoc **heredoc)
{
	*heredoc = ft_calloc(sizeof(t_heredoc), 1);
	if (!(*heredoc))
		return ;
	(*heredoc)->export = export;
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
		data->file = join_free("/tmp/.hd_tmp", ft_itoa(i));
		data->name = ignore_quote(tmp->file);
		get_here_data(data);
		data->fd = get_input(data, tmp);
		close(data->fd);
		free(data->file);
		tmp = tmp->next;
	}
	free_redir(data->lst);
}

int	heredoc_built(char *str, t_export *export)
{
	int		i;
	int		status;
	pid_t	hd_pid;
	t_heredoc	*data;

	data = NULL;
	init_heredoc(export, &data);
	hd_pid = fork();
	i = 1;
	if (hd_pid < 0)
		perror("fork");
	else if (hd_pid == 0)
	{
		do_heredoc(str, data, i);
		free_export(export);
		free(data);
		exit(0);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(hd_pid, &status, 0);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 130)
		{
			free(data);
			return (130);
		}
	}
	return (0);
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

int	main(int ac, char **av, char **env)
{
	char	*str;
	t_chunk	*chunks;
	t_export	*export = NULL;
	t_expander	*expander;
	t_ast		*ast;

	export = ms_envcpy(env);
	start_signal(ac, av, env);
	ms_readhistory();
	while (1)
	{
		str = NULL;
		str = ft_readline(export);
		if (is_void(str) && is_error(str))
			continue ;
		if (one_hd(str))
		{
			if (heredoc_built(str, export) != 0)
				continue ;
		}
		chunks = NULL;
		chunks = lexing(str);
		free(str);
		expander = NULL;
		expander = expand_str(chunks, export);
		free_chunks(chunks);
		if (expander)
		{
			if (handle_exit(expander, export))
				continue ;
			ast = NULL;
			ast = parse_args(expander, 1);
			free_expander(expander);
			pipe_check(ast, export, env);
			// free_ast(ast);
		}
		else
			continue ;
	}
	free_export(export);
}
