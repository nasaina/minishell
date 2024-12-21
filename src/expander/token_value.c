/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandrian <nandrian@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 08:10:25 by nandrian          #+#    #+#             */
/*   Updated: 2024/12/21 15:27:40 by nandrian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*expander(char *str, t_env *env)
{
	int		i;
	char	*result;
	int		status;

	result = NULL;
	status = 0;
	if (!str)
		return (NULL);
	i = 0;
	get_t_env(env);
	while (str[i])
	{
		if (i >= (int)ft_strlen(str))
			break ;
		if (insert_char(&result, str, &status, &i) == 1)
			continue ;
		if (i >= (int)ft_strlen(str))
			break ;
	}
	return (result);
}

t_chunk	*expand_token(char *result, int is_quote, t_type type)
{
	int		i;
	char	**split;
	t_chunk	*chunks;

	chunks = NULL;
	if (is_quote == 0)
	{
		i = 0;
		split = ft_split(result, 32);
		if (!split)
			return (NULL);
		while (split[i])
		{
			add_chunks_back(&chunks, split[i], type);
			free(split[i]);
			i++;
		}
		free(split);
	}
	else
		add_chunks_back(&chunks, result, WORD);
	free(result);
	return (chunks);
}

int	is_nword(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '$' || str[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

int	check_split(char **str)
{
	if (!str[1])
		return (1);
	return (0);
}

t_chunk	*expanded2(char *str, t_env *env, t_type type)
{
	int		i;
	char	*result;
	char	*name;
	t_chunk	*token = NULL;
	char	**split = NULL;
	int		status;
	int		d_status;
	char	*tmp;

	i = 0;
	result = NULL;
	i = 0;
	tmp = NULL;
	status = 0;
	d_status = 0;
	if (!is_nword(str))
	{
		add_chunks_back(&token, str, type);
		return (token);
	}
	while (str[i])
	{
		while (str[i] && (str[i] != '\'' && str[i] != '"' && str[i] != '$' && status != 1))
		{
			result = join_char(result, str[i]);
			i++;
		}
		if (str[i] && str[i] == '$' && str[i + 1] && str[i + 1] == '$'  && status != 1)
		{
			result = join_char(result, '$');
			i += 2;
			continue ;
		}
		if (str[i] && str[i] == '"' && status != 1)
		{
			i++;
			while (str[i] && str[i] != '"')
			{
				if (str[i] && str[i] == '$' && str[i + 1] && str[i + 1] == '?')
				{
					ms_exitstatus(&result, &i);
					continue ;
				}
				else if (str[i] && str[i] == '$' && str[i + 1])
				{
					name_token(str, &i, &name);
					env_value(&result, &i, env, name);
					free(name);
				}
				else
				{
					result = join_char(result, str[i]);
					i++;
				}
				if (i > (int)ft_strlen(str))
					break ;
			}
			if (str[i] && str[i] == '"')
			{
				i++;
				continue ;
			}
		}
		else if (str[i] && str[i] == '\'' && status != 1)
		{
			i++;
			while (str[i] && str[i] != '\'')
			{
				result = join_char(result, str[i]);
				i++;
			}
			if (str[i] && str[i] == '\'')
			{
				i++;
				continue ;
			}
		}
		else if (str[i] && str[i] == '$' && str[i + 1]  && status != 1)
		{
			status = 1;
			tmp = NULL;
			if (name_token(str, &i, &name))
			{
				free(name);
				status = 0;
				continue ;
			}
			env_value(&tmp, &i, env, name);
			if (!tmp)
			{
				status = 0;
				continue ;
			}
			split = ft_split(tmp, 32);
			if (check_split(split))
			{
				free(split[0]);
				free(split);
				result = join_free(result, tmp, 0);
				status = 0;
			}
			free(tmp);
			free(name);
		}
		if (status == 1)
		{
			printf("\n0%d\n", status);
			result = join_free(result, split[0], 0);
			add_chunks_back(&token, result, WORD);
			int	j = 1;
			if (!split[j])
				continue ;
			while (split[j + 1])
			{
				add_chunks_back(&token, split[j], WORD);
				free(split[j]);
				j++;
			}
			result = join_free(NULL, split[j], 1);
			free(split);
			status = 0;
		}
	}
	if (!str[i] && status != 1)
		add_chunks_back(&token, result, WORD);
	return (token);
}

t_expander	*expand_str(t_chunk *chunks, t_env *env)
{
	t_expander	*expander;
	t_chunk		*tmp;
	t_chunk		*token;
	t_chunk		*temp;

	tmp = chunks;
	expander = NULL;
	if (!tmp)
		return (NULL);
	while (tmp)
	{
		token = NULL;
		token = expanded2(tmp->str, env, tmp->type);
		temp = token;
		temp = token;
		while (temp)
		{
			add_expanders_back(&expander, temp->str, temp->type);
			temp = temp->next;
		}
		tmp = tmp->next;
		free_chunks(token);
		// token = NULL;
		// token = expanded(tmp->str, tmp->type, env);
		// temp = token;
		// while (temp)
		// {
		// 	add_expanders_back(&expander, temp->str, temp->type);
		// 	temp = temp->next;
		// }
		// tmp = tmp->next;
		// free_chunks(token);
	}
	return (expander);
}
