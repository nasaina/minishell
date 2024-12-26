/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:43:31 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/26 11:06:00 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <minishell.h>

int		is_error(char *str);
int		is_void(char *str);
int		check_next(char *str, int i);
int		isredirection(char c);
int		is_redirok(char *str, int i);
int		check_redirection(char *str);
char	*ft_readline(void);
void	ignore_args(int ac, char **av, char **env);

#endif