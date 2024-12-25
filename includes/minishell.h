/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:32:07 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/25 17:23:35 by maandria         ###   ########.fr       */
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

char		*check_path(char **pathlist, t_ast *ast, int *status);
char		*check_access(t_ast *ast);
int			exec_cmd(t_ast *ast, t_env *env);
int			check_cmd(t_ast *ast, t_env *env);
void		handle_sigint(int sig);
void		handle_sigquit(int sig);
void		free_chunks(t_chunk *lst);
int			exec_pipe(t_ast *ast, t_env *env, char **envp);
int			pipe_check(t_ast *ast, t_env *env, char **envp);
int			exec_pipe_left(t_ast *ast, t_env *env,
				char **envp, int *pipe_fds);
int			exec_pipe_right(t_ast *ast, t_env *env,
				char **envp, int *pipe_fds);
int			do_redir(t_ast *ast);
void		free_ast(t_ast *ast);
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
int			check_args(t_ast *ast);
int			is_command(t_ast *ast);
char		**take_env(t_env *env);
void		free_tab(char **str);
int			do_fork(t_ast *ast, t_env *env, char *path);
int			exec_fork(t_ast *ast, char *path, t_env *env);
int			str_isnum(char *str);
int			isbuiltin(t_ast *ast);
void		path_error(t_ast *ast, char *str);
int			error_command(t_ast *ast, char *path, char **envp);
char		*takepath_and_free(char *command, char **pathlist);
void		free_tab(char **str);
char		**create_dir(void);
void		close_fds(int *pipe_fds);
int			create_pipe(int *pipe_fds);
int			create_fork(pid_t *pid, char *str);
int			wait_children(pid_t pid_left, pid_t pid_right, int *status, int *status_left);

#endif
