/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 08:03:05 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/20 08:03:39 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_writestatus(int status)
{
	int		fd;
	char	*str;

	fd = open(".ms_status", O_CREAT | O_WRONLY | O_TRUNC, 0777);
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

	fd = open(".ms_status", O_RDONLY);
	if (fd == -1)
	{
		join_free(*result, "0", 0);
		*i += 2;
		return ;
	}
	str = get_next_line(fd);
	if (!str)
	{
		*i += 2;
		return ;
	}
	len = ft_strlen(str);
	str[len] = 0;
	*result = join_free(*result, str, 0);
	free(str);
	*i += len + 1;
	close(fd);
}
