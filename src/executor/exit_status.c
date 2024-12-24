/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 08:03:05 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/24 08:17:20 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_writestatus(int status)
{
	int		fd;
	char	*str;

	fd = open("/tmp/.ms_status", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd == -1)
		return ;
	str = ft_itoa(status);
	ft_putstr_fd(str, fd);
	free(str);
	close(fd);
}

void	ms_exitstatus(char **result, int *i)
{
	int		fd;
	char	*str;
	int		len;

	fd = open("/tmp/.ms_status", O_RDONLY);
	if (fd == -1)
	{
		*result = join_free(*result, ft_itoa(0), 2);
		*i += 1;
		return ;
	}
	str = get_next_line(fd);
	if (!str)
	{
		*result = join_free(*result, ft_itoa(0), 2);
		*i += 1;
		close(fd);
		return ;
	}
	len = ft_strlen(str);
	str[len] = 0;
	*result = join_free(*result, str, 0);
	free(str);
	*i += 1;
	close(fd);
}

int	exit_status(void)
{
	int		fd;
	int		status;
	char	*str;

	fd = open("/tmp/.ms_status", O_RDONLY);
	if (fd == -1)
		return (0);
	str = get_next_line(fd);
	if (!str)
	{
		close(fd);
		return (0);
	}
	status = ft_atoi(str);
	free(str);
	return (status);
}
