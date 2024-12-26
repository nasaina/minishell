/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:00:51 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/26 13:03:17 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_heredoc	*get_here_data(t_heredoc *heredoc)
{
	static t_heredoc	*data;

	if (heredoc == NULL)
		return (data);
	else
		data = heredoc;
	return (data);
}

t_chunk	*get_token_data(t_chunk *chunks)
{
	static t_chunk	*data;

	if (chunks == NULL)
		return (data);
	else
		data = chunks;
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
			if (!tmp)
				break ;
		}
		data->file = join_free(".hd_tmp", ft_itoa(i), 1);
		data->name = ignore_quote(tmp->file);
		get_input(data, tmp);
		close(data->fd);
		free(data->file);
		tmp = tmp->next;
	}
	free_redir(data->lst);
}

int	heredoc_built(char *str, t_env *env, t_chunk *chunks)
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
		get_token_data(chunks);
		do_heredoc(str, data, i);
		free_env(env);
		free(data);
		free_chunks(chunks);
		exit(0);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(hd_pid, &status, 0);
	signal(SIGINT, &global_sigint);
	return (check_hdstatus(status, data));
}

int	one_hd(char *str)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			i++;
			status = 1;
			while (str[i] && str[i] != '\'' && str[i] != '"')
				i++;
			if (str[i])
				status = 0;
		}
		if (str[i] && str[i] == '<' && str[i + 1] == '<' && status == 0)
			return (1);
		if (i < (int)ft_strlen(str))
			i++;
	}
	return (0);
}
