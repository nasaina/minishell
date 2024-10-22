/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 07:48:44 by nandrian          #+#    #+#             */
/*   Updated: 2024/10/14 08:45:50 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include <lexer.h>
# include <exec.h>

typedef struct s_expander
{
	t_type				type;
	char				*cmd;
	struct s_expander	*next;	
}	t_expander;

t_expander	*expand_str(t_chunk *chunks, t_export *export);
char		*get_name(char *str);
char		*get_value(char *str);
char		*ms_getenv(char *str, t_export *export);
char		*ms_get(char *str, t_export *export);
void		add_expanders_back(t_expander **args, char *str, t_type type);
void		free_expander(t_expander *expander);
void		ms_unset(t_export **export, t_expander *expander);
void		ms_printenv(t_export *export, t_expander *expander);

#endif