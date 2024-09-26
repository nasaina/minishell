/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:38:08 by nandrian          #+#    #+#             */
/*   Updated: 2024/09/26 16:14:33 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	count_cmd(t_chunk *chunks)
{
	int	i;

	i = 1;
	while (chunks)
	{
		if (chunks->str[0] == 124)
			i++;
		chunks = chunks->next;
	}
	return (i);
}

t_cmd	*get_cmd(t_chunk *chunks)
{
	int		i;
	int		count;
	t_cmd	*cmd;

	count = count_cmd(chunks);
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	cmd->args = (char **)malloc(count + 1 * sizeof(char *));
	i = 0;
	while (chunks && chunks->str[0] != 124)
	{
		cmd->args[i] = ft_strdup(chunks->str);
		chunks = chunks->next;
		i++;
	}
	cmd->args[i] = NULL;
	return (cmd);
}

t_ast	*parse_args(t_chunk *chunks)
{
	int		i;
	int		count;
	t_ast	*tmp;
	t_ast	*ast;
	t_cmd	*cmd;

	cmd = NULL;
	count = count_cmd(chunks);
	ast = (t_ast *)malloc(sizeof(t_ast));
	while (chunks)
	{
		while (chunks->str[0] != 124)
		{
			
			ast->type = COMMAND;
		}
		
		chunks = chunks->next;
	}
	return (ast);
}
