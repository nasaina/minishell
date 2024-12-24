/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:31:44 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/24 10:53:43 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <minishell.h>
# include <parser.h>

typedef struct s_env
{
	char			*env;
	struct s_env	*next;
}	t_env;

int		ft_strcmp(char *s1, char *s2);
t_env	*ms_envcpy(char **env);
void	env_back(t_env **env, char *str);
void	free_env(t_env *env);
char	**path_list(t_env *env);
int		redir_out(t_ast *ast, t_redir *redir);
int		redir_in(t_ast *ast, t_redir *redir);
int		redir_heredoc(t_ast *ast);
int		redir_append(t_ast *ast, t_redir *redir);
int		redir_error(int fd, char *str, t_ast *ast);
void	global_sigint(int sig);
int		exit_status(void);

#endif