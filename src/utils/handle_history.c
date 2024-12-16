/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:20:58 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/16 17:12:13 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_writehistory(char *str)
{
	int	fd;

	fd = open("/tmp/.ms_history", O_CREAT | O_WRONLY | O_APPEND, 0777);
	ft_putendl_fd(str, fd);
	close(fd);
}

void	ms_readhistory(void)
{
	int		fd;
	char	*str;
	char	*result;
	size_t	i;

	fd = open("/tmp/.ms_history", O_RDONLY);
	if (fd == -1)
		return ;
	str = get_next_line(fd);
	while (str != NULL)
	{
		i = 0;
		while (str[i] && str[i] != '\n')
			i++;
		result = ft_calloc(i + 2, 1);
		ft_strlcat(result, str, i + 1);
		add_history(result);
		free(str);
		free(result);
		str = get_next_line(fd);
	}
	close(fd);
}
