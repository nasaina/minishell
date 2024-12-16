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

void	do_heredoc(char *str, t_export *export, int i)
{
	char 	*file;
	t_redir	*heredoc;
	t_redir	*tmp;

	file = NULL;
	tmp = expand_hdoc(str);
	free(str);
	heredoc = tmp;
	while (heredoc)
	{
		if (heredoc->type == PIPE)
		{
			i++;
			heredoc = heredoc->next;
		}
		file = join_free(".tmp", ft_itoa(i));
		get_input(heredoc, export, file);
		free(file);
		heredoc = heredoc->next;
	}
	free_redir(tmp);
	free_export(export);
	exit (0);
}

char	*heredoc_built(char *str, t_export *export)
{
	int		status;
	pid_t	hd_pid;
	char	*file;
	int		i;

	file = NULL;
	hd_pid = fork();
	i = 1;
	if (hd_pid < 0)
		perror("fork");
	else if (hd_pid == 0)
		do_heredoc(str, export, i);
	waitpid(hd_pid, &status, 0);
	return (file);
}

int	one_hd(char *str)
{
	int	i;

	i = 0;
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
	while (1)
	{
		str = NULL;
		str = ft_readline(str, export);
		if (is_void(str) && is_error(str))
			continue ;
		if (one_hd(str))
			heredoc_built(str, export);
		chunks = NULL;
		chunks = lexing(str);
		free(str);
		expander = NULL;
		expander = expand_str(chunks, export);
		free_chunks(chunks);
		if (expander)
		{
			ast = NULL;
			ast = parse_args(expander, 1);
			free_expander(expander);
			pipe_check(ast, export, env);
			free_ast(ast);
		}
		else
			continue ;
	}
	free_export(export);
}
