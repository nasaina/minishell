#include <minishell.h>

void	start_signal(int ac, char **av, char **env)
{
	ignore_args(ac, av, env);
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

void	heredoc_built(char *str, t_export *export)
{
	int		status;
	pid_t	hd_pid;
	t_redir *heredoc;

	hd_pid = fork();
	if (hd_pid < 0)
		perror("fork");
	else if (hd_pid == 0)
	{
		heredoc = expand_hdoc(str);
		while (heredoc)
		{
			get_input(heredoc, export);
			heredoc = heredoc->next;
		}
		exit (0);
	}
	waitpid(hd_pid, &status, 0);
}

int	main(int ac, char **av, char **env)
{
	char	*str = NULL;
	t_chunk	*chunks = NULL;
	t_export	*export = NULL;
	t_expander	*expander = NULL;
	t_ast		*ast = NULL;

	export = ms_envcpy(env);
	start_signal(ac, av, env);
	// signal(SIGINT, handle_sigint);
	// signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		str = ft_readline(str);
		if (is_void(str) && is_error(str))
			continue ;
		chunks = lexing(str);
		if (heredoc_check(chunks))
			heredoc_built(str, export);
		expander = expand_str(chunks, export);
		if (expander)
		{
			ast = parse_args(expander);
			free_expander(expander);
			pipe_check(ast, export, env);
			free_ast(ast);
		}
		else
			continue ;
	}
	free_export(export);
}
