/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 09:08:39 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/20 07:37:59 by nandrian         ###   ########.fr       */
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

void	free_env(t_env *env)
{
	t_env	*tmp;

	if (!env)
		return ;
	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->env);
		free(tmp);
	}
	free(env);
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
	int	i;

	if (!ast)
		return ;
	if (ast->type == AST_CMD)
	{
		i = 0;
		while (ast->cmd->args[i])
		{
			free(ast->cmd->args[i]);
			i++;
		}
		free(ast->cmd->args);
		free_redir(ast->cmd->redir);
		free(ast->cmd);
	}
	free_ast(ast->left);
	free_ast(ast->right);
	free(ast);
}
