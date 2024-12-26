/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 13:40:18 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/26 13:40:30 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
