/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:35:55 by mal-mora          #+#    #+#             */
/*   Updated: 2024/05/27 11:42:16 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_real_char(char c)
{
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}
int end_of_proccessing(char c)
{
	return (c == '$' || c == DOUBLE_QUOTE || c == SINGLE_QUOTE || c == '\0');
}
char *allocate_for_expand(char *str, int *pos)
{
	int i;
	int len;
	int len_env;
	char *new_s;
	char *res;
	char *reset;

	len = 0;
	len_env = 0;
	i = 0;
	while (!end_of_proccessing(str[i++]))
		len++;
	i = 0;
	while (is_real_char(str[i++]))
		len_env++;
	new_s = malloc(len_env + 1);
	if (!new_s)
		return (NULL);
	i = 0;
	while (i < len_env)
	{
		new_s[i] = str[i];
		i++;
	}
	new_s[i] = '\0';
	i = 0;
	while (!end_of_proccessing(str[i++]))
		(*pos)++;
	reset = ft_substr(str, len_env, len - len_env);
	res = ft_strjoin(getenv(new_s), reset);
	return (res);
}
char *handel_singleq(char *s, int *pos)
{
	char *res;
	int len;
	int i;

	i = 0;
	len = 0;
	while (s[i++] != SINGLE_QUOTE)
		len++;
	res = ft_substr(s, 0, len);
	i = 0;
	while (s[i++] != SINGLE_QUOTE)
		(*pos)++;
	return res;
}


char *expand_str(char *s)
{
	int i;
	char *result = NULL;
	char *befor_dollar;
	char *res = ft_strdup("");
	int counter;
	int mlen = 0;
	int flag = 0;
	char *new_str;
	int id;
	
	counter = 0;
	i = 0;
	while (s[i])
	{
		if (!end_of_proccessing(s[i]))
			i++;
		else
			break;
	}
	befor_dollar = ft_substr(s, 0, i);
	while (s[i])
	{
		if (s[i] == DOUBLE_QUOTE)
			res = handel_expand_dq(s + (++i), &i);
		else if (s[i] == SINGLE_QUOTE)
			(res = handel_singleq(s + (++i), &i), flag = 1);
		else if (s[i] == '$')
			res = allocate_for_expand(s + (++i), &i);
		id = i + 1;
		if (!counter)
			result = ft_strjoin(befor_dollar, res);
		else
			result = ft_strjoin(result, res);
		if (flag)
		{
			while (!end_of_proccessing(s[++i]))
				mlen++;
			new_str = ft_substr(s, id, mlen);
			result = ft_strjoin(result, new_str);
		}
		counter++;
	}
	return result;
}

void *handel_expanding(t_lexer **lexer)
{
	t_lexer *tmp;

	tmp = *lexer;
	while (tmp)
	{
		if (str_chr(tmp->str, '$') == -1)
			break;
		tmp->str = expand_str(tmp->str);
		if (tmp->str == NULL)
			return NULL;
		if (*tmp->str == '\0')
			ft_lst_remove(lexer, tmp->i);
		tmp = tmp->next;
	}
	return *lexer;
}
