/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:24:41 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/22 17:45:10 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <minishell.h>

char	*env_name(char *str);
int		double_input(char **str, int i, char *args);
int		is_invalidname(char *str);
int		check_status(char **args);
int		check_input(char **args, int i, char *name);
int		add_input(t_env *env, int i, char **args);
int		ms_printenv(t_ast *ast, t_env *env);
t_env	*ms_envcpy(char **envp);
void	sort_env(t_env **env);
void	ft_printenv(t_env *env, int *i);
void	print_env(t_env *env);
int		ms_env(char **str, t_env *env);
char	**init_builtins(void);
int		ms_builtins(t_ast *ast, t_env *env);
t_env	*get_env(char *str);
t_env	*env_last(t_env *env);
void	env_back(t_env **env, char *str);
int		ft_exit(t_expander *expander, t_env *env);
int		handle_exit(t_expander *expander, t_env *env);
char	*get_home(t_env *env);
char	*get_cd(char *str, char *last_direcotry, t_env *env);
char	*last_dir(t_env *env);
int		get_oldpwd(t_ast *ast, char *dir, char *last_directory, t_env *env);
int		ms_cd(t_ast *ast, t_env *env);
int		is_echoflag(char *str);
int		echo_flagonly(char **str);
void	echo_monitor(char **str, int i);
int		ms_echo(t_cmd *cmd);
int		ms_pwd(t_ast *ast);
void	change_env_pwd(t_env *env);
void	change_env_oldpwd(t_env *env, char *cwd);
int		len_to_equal(char *str);
char	*var_remove(char *str);
void	remove_env(t_env **env, char *str);
int		ms_unset(t_env **env, char **str);
void	is_double(t_env **env, char *name);
int		ms_printenv(t_ast *ast, t_env *env);

#endif