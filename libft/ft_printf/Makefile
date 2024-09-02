# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nandrian <nandrian@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/05 13:33:43 by nandrian          #+#    #+#              #
#    Updated: 2024/07/04 17:11:05 by nandrian         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT :

NAME	= libftprintf.a

CC		= cc

CFLAGS	= -Wall -Werror -Werror

OBJ		= $(SRC:.c=.o)

SRC		=	ft_printf.c ft_putadr.c ft_putchar_len.c ft_putnbr_hex.c \
			ft_putnbr.c ft_putstr_len.c ft_strchr.c

all		: $(NAME)

$(NAME)	: $(OBJ)
	@ar -rcs $(NAME) $(OBJ)

&.o : %.c
	@$(CC) $(CFLAGS) -o $@ -c $<

clean	:
	@rm -rf *.o

fclean	: clean
	@rm -rf $(NAME)

re		: fclean all
