/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:35:55 by mal-mora          #+#    #+#             */
/*   Updated: 2024/05/30 18:00:05 by mal-mora         ###   ########.fr       */
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

char *first_check(char *s, int *i, int *flag)
{
	char *res;
	
	if (s[*i] == DOUBLE_QUOTE)
		res = handel_expand_dq(s + (++(*i)), i);
	else if (s[*i] == SINGLE_QUOTE)
	{
		res = handel_singleq(s + (++(*i)), i);
		*flag = 1;	
	}
	else if (s[*i] == '$')
		res = alloc_exp(s + (++(*i)), i);
	else
		return NULL;
	return res;
}
char	*expand_str(char *s)
{
	int		i;
	char	*result = NULL;
	char	*befor_dollar;
	int		counter;
	int		flag;

	counter = 0;
	i = 0;
	flag = 0;
	while (s[i] && !end_of_proccessing(s[i]))
		i++;
	befor_dollar = ft_substr(s, 0, i);
	while (s[i])
	{
		if (!counter)
			result = ft_strjoin(befor_dollar, first_check(s, &i, &flag));
		else
			result = ft_strjoin(result, first_check(s, &i, &flag));
		if (flag)
			result = if_single_q(s, &i, result);
		(free(befor_dollar));
		// if(result[0] == DOUBLE_QUOTE && s[0] == SINGLE_QUOTE)
		// 	return expand_str(result);
		// printf("%s %d", result , i);
		// exit(0);
		counter++;
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
		tmp->str = expand_str(tmp->str);
		if (*tmp->str == '\0')
			ft_lst_remove(lexer, tmp->i);
		tmp = tmp->next; 
	}
}
