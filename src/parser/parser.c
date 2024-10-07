/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:38:08 by nandrian          #+#    #+#             */
/*   Updated: 2024/10/07 10:53:50 by nandrian         ###   ########.fr       */
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

int	count_chunks(t_chunk *chunks)
{
	int	i;

	i = 0;
	while (chunks && chunks->type != PIPE)
	{
		i++;
		chunks = chunks->next;
	}
	return (i);
}

t_cmd	*get_cmd(t_chunk **chunks)
{
	int		i;
	int		count;
	t_cmd	*cmd;

	count = count_chunks(*chunks);
	printf("\n count %d\n", count);
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	cmd->args = (char **)malloc((count + 1) * sizeof(char *));
	i = 0;
	while (*chunks && (*chunks)->str[0] != 124)
	{
		cmd->args[i] = ft_strdup((*chunks)->str);
		*chunks = (*chunks)->next;
		i++;
	}
	return (cmd);
}

t_ast	*parse_args(t_chunk *chunks)
{
	t_ast	*tmp;
	t_ast	*root;

	tmp = malloc(sizeof(t_ast));
	tmp->type = AST_COMMAND;
	tmp->cmd = get_cmd(&chunks);
	tmp->left = NULL;
	tmp->right = NULL;
	if (chunks && chunks->type == PIPE)
	{
		root = malloc(sizeof(t_ast));
		root->type = AST_PIPE;
		root->cmd = NULL;
		root->left = tmp;
		chunks = chunks->next;
		root->right = parse_args(chunks);
		return (root);
	}
	return (tmp);
}
