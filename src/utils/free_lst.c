/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 09:08:39 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/08 15:21:12 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_chunks(t_chunk *lst)
{
	t_chunk	*tmp;

	if (!lst)
		return ;
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp->str);
		free(tmp);
	}
	free(lst);
}

void	free_expander(t_expander *expander)
{
	t_expander	*tmp;

	if (!expander)
		return ;
	while (expander)
	{
		tmp = expander;
		expander = expander->next;
		free(tmp->cmd);
		free(tmp);
	}
	free(expander);
}

void	free_export(t_export *export)
{
	t_export	*tmp;

	if (!export)
		return ;
	while (export)
	{
		tmp = export;
		export = export->next;
		free(tmp->env);
		free(tmp);
	}
	free(export);
}

void	free_redir(t_redir *redir)
{
	t_redir	*tmp;

	if (!redir)
		return ;
	while (redir)
	{
		tmp = redir;
		redir = redir->next;
		free(tmp->file);
		free(tmp);
	}
	free(redir);
}

void	free_ast(t_ast *ast)
{
	if (!ast)
		return;
	if (ast->type == AST_CMD)
	{
		int i = 0;
		while (ast->cmd->args[i])
		{
			free(ast->cmd->args[i]);
			i++;
		}
		free(ast->cmd->args);
		free_redir(ast->cmd->redir);
	}
	free_ast(ast->left);
	free_ast(ast->right);
}
