/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:38:08 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/24 10:34:28 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	count_cmd(t_expander *expander)
{
	int	i;

	i = 1;
	while (expander)
	{
		if (expander->type == PIPE)
			i++;
		expander = expander->next;
	}
	return (i);
}

int	count_token(t_expander *expander)
{
	int	i;

	i = 0;
	while (expander && expander->type != PIPE)
	{
		i++;
		expander = expander->next;
	}
	return (i);
}

t_redir	*get_redir(t_expander **expander, t_redir *redir)
{
	t_type	type;

	type = (*expander)->type;
	*expander = (*expander)->next;
	if (*expander == NULL)
		return (NULL);
	add_redir_back(&redir, (*expander)->cmd, type);
	*expander = (*expander)->next;
	return (redir);
}

t_cmd	*get_cmd(t_expander **expander)
{
	int		i;
	int		count;
	t_cmd	*cmd;

	count = count_token(*expander);
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	cmd->args = (char **)ft_calloc((count + 1), sizeof(char *));
	cmd->redir = NULL;
	i = 0;
	while (*expander && (*expander)->type != PIPE)
	{
		if ((*expander)->type == WORD)
		{
			cmd->args[i] = ft_strdup((*expander)->cmd);
			*expander = (*expander)->next;
			i++;
		}
		else
			cmd->redir = get_redir(expander, cmd->redir);
	}
	if (*expander == NULL)
		cmd->args[i] = NULL;
	return (cmd);
}

t_ast	*parse_args(t_expander *expander, int file)
{
	t_ast	*tmp;
	t_ast	*root;

	tmp = malloc(sizeof(t_ast));
	tmp->type = AST_CMD;
	if (expander)
		tmp->cmd = get_cmd(&expander);
	tmp->file = file;
	tmp->status = 0;
	tmp->left = NULL;
	tmp->right = NULL;
	if (expander && expander->type == PIPE)
	{
		root = malloc(sizeof(t_ast));
		root->type = AST_PIPE;
		root->cmd = NULL;
		root->status = 0;
		root->left = tmp;
		expander = expander->next;
		file += 1;
		root->right = parse_args(expander, file);
		return (root);
	}
	return (tmp);
}
