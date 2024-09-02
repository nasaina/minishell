/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 10:45:33 by nandrian          #+#    #+#             */
/*   Updated: 2024/07/04 15:57:30 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

void	ft_putadr(void *c, int *len);
void	ft_putchar_len(int c, int *len);
void	ft_putnbr_hex(unsigned int c, unsigned int base, int upcase, int *len);
void	ft_putnbr_len(int c, int *len);
void	ft_putstr_len(char *str, int *len);
int		ft_strchr_len(const char *s, int c);
int		ft_printf(const char *format, ...);

#endif
