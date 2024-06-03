/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:35:55 by mal-mora          #+#    #+#             */
/*   Updated: 2024/06/02 20:56:46 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *alloc_exp(char *str, int *pos)
{
	int i;
	int len_env;
	char *new_s;
	char *res;
	char *reset;
	len_env = 0;
	i = 0;

	while (is_real_char(str[i++]))
		len_env++;
	new_s = ft_strncpy(str, len_env);
	if (!new_s)
		return NULL;
	i = 0;
	while (!end_of_proccessing(str[i++]))
		(*pos)++;
	reset = ft_substr(str, len_env, get_len_ep(str) - len_env);
	res = ft_strjoin(getenv(new_s), reset);
	return (res);
}
char *expand_str(char *s)
{
	int i;
	char *result = NULL;
	char *befor_dollar;
	int counter;
	int flag;

	counter = 0;
	i = 0;
	flag = 0;
	while (s[i] && s[i] != '$')
		i++;
	befor_dollar = ft_substr(s, 0, i);
	while (s[i])
	{
		if (!counter)
			result = ft_strjoin(befor_dollar, alloc_exp(s + (++i), &i));
		else
			result = ft_strjoin(result, alloc_exp(s + (++i), &i));
		if(s[i] != '$')
		{
			int k = i;
			while (s[i] && s[i] != DOUBLE_QUOTE)
				i++;
			result = ft_strjoin(result, ft_substr(s, k, i - k + 1));
		}
		counter++;
	}
	return (result);
}

char *expand_str2(char *s)
{
	int i;
	int j;
	char *result;
	int k = 0;
	char *res;
	
	j = 0;
	i = 0;
	result = NULL;
	while (s[i])
	{
		j = 0;
		k = 0;
		if (s[i] == DOUBLE_QUOTE)
		{
			k = ++i;
			while (s[i])
			{
				if (s[i] == DOUBLE_QUOTE)
				{
					res = ft_substr(s, k, j);
					result = ft_strjoin(result, res);
					if (str_chr(res, '$') != -1)
						result = expand_str(result);
					break;
				}
				j++;
				i++;
			}
		}
		else if(s[i] == SINGLE_QUOTE)
		{
			
			k = ++i;
			while (s[i])
			{
				if (s[i] == SINGLE_QUOTE)
				{
					result = ft_strjoin(result, ft_substr(s, k, j));
					break;
				}
				j++;
				i++;
			}
		}
		else if(s[i] == '$')
		{
			result = ft_strjoin(result, alloc_exp(s + (++i), &i));
			i--;
		}
		else
			result = ft_strjoin(result, ft_substr(&s[i], 0, 1));
		i++;
	}
	return (result);
}

void handel_expanding(t_lexer **lexer)
{
	t_lexer *tmp;

	tmp = *lexer;
	while (tmp)
	{
		if (str_chr(tmp->str, '$') == -1)
		{
			tmp = tmp->next;
			continue;
		}
		tmp->expanded = 1;
		tmp->str = expand_str2(tmp->str);
		if (*tmp->str == '\0')
			ft_lst_remove(lexer, tmp->i);
		tmp = tmp->next;
	}
}
