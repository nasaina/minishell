/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:00:51 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/24 13:15:05 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_heredoc	*get_here_data(t_heredoc *heredoc)
{
	static t_heredoc	*data = NULL;

	if (heredoc == NULL)
		return (data);
	data = heredoc;
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
		data->fd = get_input(data, tmp);
		get_here_data(data);
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
