/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:32:07 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/22 17:13:33 by nandrian         ###   ########.fr       */
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

char		**init_builtins(void);
char		*check_path(char **pathlist, t_ast *ast);
char		*check_access(t_ast *ast);
int			isbuiltin(t_ast *ast);
int			exec_cmd(t_ast *ast, t_env *env);
int			check_cmd(t_ast *ast, t_env *env);
void		handle_sigint(int sig);
void		handle_sigquit(int sig);
void		free_chunks(t_chunk *lst);
int			ms_pwd(t_ast *ast);
int			ms_cd(t_ast *ast, t_env *env);
int			exec_pipe(t_ast *ast, t_env *env, char **envp);
int			pipe_check(t_ast *ast, t_env *env, char **envp);
int			str_isnum(char *str);
int			table_isnum(char **str);
int			ms_echo(t_cmd *cmd);
int			ms_env(char **str, t_env *env);
int			ms_unset(t_env **env, char **str);
int			ms_builtins(t_ast *ast, t_env *env);
void		exec_pipe_left(t_ast *ast, t_env *env,
				char **envp, int *pipe_fds);
int			exec_pipe_right(t_ast *ast, t_env *env,
				char **envp, int *pipe_fds);
char		*var_remove(char *str);
void		do_redir(t_ast *ast);
void		remove_env(t_env **env, char *str);
void		free_ast(t_ast *ast);
t_env		*ms_envcpy(char **env);
void		sort_env(t_env **env);
void		ft_printenv(t_env *env, int *i);
void		print_env(t_env *env);
void		is_double(t_env **env, char *name);
int			check_input(char **args, int i, char *name);
int			double_input(char **str, int i, char *args);
int			is_invalidname(char *str);
char		*env_name(char *str);
int			hdoc_oneword(char *str, int i, t_type *type);
int			hdoc_count(char *str, int i, t_type *type);
t_chunk		*hdoc_token(char *str);
int			is_variable(char *str);
t_redir		*expand_hdoc(char *str);
char		*join_free(char *s1, char *s2, int status);
char		*ignore_quote(char	*str);
void		ms_exitstatus(char **result, int *i);
void		ms_writestatus(int status);
t_env		*get_t_env(t_env *export);
void		ms_writestatus(int status);
int			check_status(char **args);
int			quote_count(char *str);
char		*ignore_quote(char	*str);
int			is_expandable(char	*str);
char		*hdoc_expander(char *str, t_env *env);
int			check_args(t_ast *ast);
void		change_env_pwd(t_env *env);
void		change_env_oldpwd(t_env *env, char *cwd);
int			is_command(t_ast *ast);
char		**take_env(t_env *env);
void		free_tab(char **str);
void		do_fork(t_ast *ast, t_env *env, char *path);
void		exec_fork(t_ast *ast, char *path, t_env *env);

#endif
