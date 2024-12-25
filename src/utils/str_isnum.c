/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_isnum.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:03:14 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/25 10:58:53 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_numerror(char *str)
{
	printf("exit\n");
	printf("minishell: exit: ");
	ft_putstr_fd(str, 2);
	ft_putstr_fd(" : numeric argument required\n", 2);
}

int	check_str(char *str, int *i)
{
	while (str[*i] && (str[*i] == 32 || str[*i] == '\t'))
		*i += 1;
	if (str[*i] && str[*i] != '+' && str[*i] != '-' && !ft_isdigit(str[*i]))
	{
		print_numerror(str);
		return (1);
	}
	if (str[*i] && (str[*i] == '+' || str[*i] == '-'))
		*i += 1;
	while (str[*i] && str[*i] != 32 && str[*i] != '\t' && ft_isdigit(str[*i]))
		*i += 1;
	if (str[*i] && !ft_isdigit(str[*i]) && str[*i] != 32 && str[*i] != '\t')
	{
		print_numerror(str);
		return (1);
	}
	while (str[*i] && (str[*i] == 32 || str[*i] == '\t'))
		*i += 1;
	return (0);
}

int	check_ifalpha(char *str, int *i)
{
	if (str[*i] == 32 || str[*i] == '\t' || ft_isdigit(str[*i])
		|| str[*i] == '+' || str[*i] == '-')
	{
		if (check_str(str, i))
			return (1);
		if (str[*i])
		{
			print_numerror(str);
			return (1);
		}
		else
			return (0);
	}
	else if (!ft_isdigit(str[*i]) && str[*i] != 32 && str[*i] != '\t'
		&& str[*i] != '+' && str[*i] != '-')
	{
		print_numerror(str);
		return (1);
	}
	else
		*i += 1;
	return (0);
}

int	str_isnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (check_ifalpha(str, &i))
			return (1);
	}
	return (0);
}
