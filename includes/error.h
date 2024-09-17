/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:43:31 by nandrian          #+#    #+#             */
/*   Updated: 2024/09/17 15:45:54 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

int		is_error(char *str);
int		check_next(char *str, int i);
int		isredirection(char c);
int		is_redirok(char *str, int i);
int		is_brace(char *str);
int		check_redirection(char *str);
char	*ft_readline(char *str);
void	ignore_args(int ac, char **av, char **env);

#endif