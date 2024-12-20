/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:32:07 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/20 07:52:44 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <includes.h>

# define NC		"\e[0m"
# define YELLOW	"\e[1;33m"
# define RED	"\e[31m"
# define GREEN	"\e[1;32m"
# define CYAN	"\e[1;36m"

typedef struct s_lexer
{
	char			c;
	struct s_lexer	*next;
}	t_lexer;

typedef struct s_heredoc
{
	int			fd;
	char		*name;
	char		*file;
	t_env		*env;
	t_redir		*lst;
}	t_heredoc;

char	**init_builtins(void);
char	*check_path(char **pathlist, t_ast *ast);
char	*check_access(t_ast *ast);
int		handle_eof(char *str, t_env *env);
int		isbuiltin(t_ast *ast);
int		exec_cmd(t_ast *ast, char **env);
int		check_cmd(t_ast *ast, t_env *env, char **envp);
void	handle_sigint(int sig);
void	handle_sigquit(int sig);
void	free_chunks(t_chunk *lst);
int		ms_pwd(t_ast *ast);
int		ms_cd(t_ast *ast, t_env *env);
int		exec_pipe(t_ast *ast, t_env *env, char **envp);
int		pipe_check(t_ast *ast, t_env *env, char **envp);
int		str_isnum(char *str);
int		table_isnum(char **str);
int		ms_echo(t_cmd *cmd);
int		ms_env(char **str, t_env *env);
int		ms_unset(t_env **env, char **str);
int		ms_builtins(t_ast *ast, t_env *env);
void	ms_export(char **envp, t_chunk *chunks);
void	exec_pipe_left(t_ast *ast, t_env *env,
			char **envp, int *pipe_fds);
int		exec_pipe_right(t_ast *ast, t_env *env,
			char **envp, int *pipe_fds);
char 	*var_remove(char *str);
void	do_redir(t_ast *ast);
void	remove_env(t_env **env, char *str);
void	free_ast(t_ast *ast);
int		get_input(t_heredoc *heredoc, t_redir *tmp);
int		heredoc_check(t_chunk *chunks);
t_redir	*expand_hdoc(char *str);
t_env	*ms_envcpy(char **env);
void		sort_env(t_env **env);
void		ft_printenv(t_env *env, int *i);
void		print_env(t_env *env);
void		is_double(t_env **env, char *name);
int			check_input(char **args, int i, char *name);
int			double_input(char **str, int i, char *args);
int			is_invalidname(char *str);
char		*env_name(char *str);
int			hdoc_oneword(char *str, int i, t_type *type);
int			hdoc_count(int count, char *str, int i, t_type *type);
t_chunk		*hdoc_token(char *str);
int			is_variable(char *str);
int			heredoc_check(t_chunk *chunks);
t_redir		*expand_hdoc(char *str);
char		*join_free(char *s1, char *s2, int status);
char	*ignore_quote(char	*str);
void	free_heredoc_data(t_heredoc *heredoc);
t_heredoc	*get_here_data(t_heredoc *heredoc);
int	is_status(char *str, int i);
void	ms_exitstatus(char **result, int *i);
void	ms_writestatus(int status);
void	add_quote(char **result);
t_env	*get_t_env(t_env *export);

#endif
