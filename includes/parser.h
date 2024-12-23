/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:38:37 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/23 08:39:39 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <lexer.h>
# include <expander.h>
# include <minishell.h>

typedef enum s_asttype
{
	AST_CMD,
	AST_PIPE,
}	t_asttype;

typedef struct s_redir
{
	t_type			type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char	**args;
	t_redir	*redir;
}	t_cmd;

typedef struct s_ast
{
	int				file;
	int				status;
	t_asttype		type;
	t_cmd			*cmd;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

void	add_redir_back(t_redir **redir, char *file, t_type type);
void	free_redir(t_redir *redir);

#endif
