/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:07:59 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/26 13:02:43 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include <minishell.h>
# include <parser.h>

typedef struct s_heredoc
{
	int			fd;
	char		*name;
	char		*file;
	t_env		*env;
	t_redir		*lst;
}	t_heredoc;

t_heredoc	*get_here_data(t_heredoc *heredoc);
void		init_heredoc(t_env *env, t_heredoc **heredoc);
void		do_heredoc(char *str, t_heredoc *data, int i);
int			heredoc_built(char *str, t_env *env, t_chunk *chunks);
int			one_hd(char *str);
int			hdoc_countsimple(char *str, int i, t_type *type);
int			hdoc_countdouble(char *str, int i, t_type *type);
int			hdoc_oneword(char *str, int i, t_type *type);
int			hdoc_count(char *str, int i, t_type *type);
int			check_hdstatus(int status, t_heredoc *data);
t_chunk		*get_token_data(t_chunk *chunks);
int			heredoc_check(t_chunk *chunks);
t_chunk		*hdoc_token(char *str);
t_redir		*expand_hdoc(char *str);
int			is_expandable(char	*str);
char		*hdoc_expander(char *str, t_env *env);
int			get_heredoc_value(t_heredoc **heredoc, char *str, t_redir *tmp);
void		get_input(t_heredoc *heredoc, t_redir *tmp);
void		free_heredoc_data(t_heredoc *heredoc);
int			is_variable(char *str);
char		*expand_heredoc(char *file, char *str, t_env *env);
int			quote_count(char *str);
char		*ignore_quote(char	*str);
int			heredoc_input(char *str, int *i, t_env *env, char **result);

#endif