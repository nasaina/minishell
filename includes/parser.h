/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:38:37 by nandrian          #+#    #+#             */
/*   Updated: 2024/10/14 14:34:54 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <lexer.h>


typedef enum s_asttype
{
	AST_CMD,
	AST_PIPE,
}	t_asttype;

typedef struct s_redir
{
	t_type		type;
	char		*redir;
	char		*file;
	struct s_redir	*next;
}	t_redir;


typedef struct s_cmd
{
	char	**args;
	t_redir	*redir;
}	t_cmd;

typedef struct s_ast
{
	t_asttype		type;
	t_cmd			*cmd;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

int		count_cmd(t_expander *expander);
int		count_token(t_expander *expander);
t_cmd	*get_cmd(t_expander **expander);
t_ast	*parse_args(t_expander *expander);

#endif
