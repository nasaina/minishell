/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:38:37 by nandrian          #+#    #+#             */
/*   Updated: 2024/10/10 20:23:13 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <lexer.h>

typedef enum s_asttype
{
	AST_COMMAND,
	AST_PIPE,
}	t_asttype;

typedef struct s_cmd
{
	char	**args;
}	t_cmd;

typedef struct s_ast
{
	t_asttype		type;
	t_cmd			*cmd;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

int		count_cmd(t_chunk *chunks);
int		count_chunks(t_chunk *chunks);
int		isbuiltin(t_cmd *cmd);
void	exec_cmd(t_cmd *cmd);
t_cmd	*get_cmd(t_chunk **chunks);
t_ast	*parse_args(t_chunk *chunks);

#endif
