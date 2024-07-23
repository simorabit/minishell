/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:35:55 by mal-mora          #+#    #+#             */
/*   Updated: 2024/07/23 15:01:29 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char *m_get_env(char *str, t_env **env_list)
{
	t_env *env;
	char *res;

	env = *env_list;
	while (env)
	{
		if (!ft_strncmp(env->content, str, ft_strlen(str)) &&
			env->content[ft_strlen(str)] == '=')
			res = get_content_from_eq_to_fin(env->content);
		env = env->next;
	}
	return res;
}
char *alloc_exp(char *str, int *pos, t_env **env_list)
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
		return (NULL);
	i = 0;
	while (!end_of_proccessing(str[i++]))
		(*pos)++;
	reset = ft_substr(str, len_env, get_len_ep(str) - len_env);
	if (!*reset)
		reset = NULL;
	res = ft_strjoin(m_get_env(new_s, env_list), reset);
	free(reset);
	return (res);
}

void *find_dollar(char *result, char *s, int *i)
{
	int k;

	if (!result)
		return (NULL);
	k = *i;
	while (s && s[*i] && s[*i] != DOUBLE_QUOTE)
		i++;
	result = ft_strjoin(result, ft_substr(s, k, (*i) - k + 1));
	return (result);
}

char *expand_str(char *s, t_env **env_list)
{
	int i;
	int counter;
	char *result;
	char *befor_dollar;

	counter = 0;
	result = NULL;
	i = 0;
	while (s[i] && s[i] != '$')
		i++;
	befor_dollar = ft_substr(s, 0, i);
	while (s[i])
	{
		if (s[i] == '$' && !counter)
			result = ft_strjoin(befor_dollar, alloc_exp(s + (++i), &i, env_list));
		else if (s[i] == '$' && counter)
			result = ft_strjoin(result, alloc_exp(s + (++i), &i, env_list));
		if (s[i] && s[i] != '$')
			result = ft_strjoin(result, ft_substr(&s[i++], 0, 1));
		if (!result)
			return (NULL);
		counter++;
	}
	free(befor_dollar);
	return (result);
}

char *expand_str2(t_lexer **tmp, t_env **env_list)
{
	int i;
	int j;
	char *result;
	char *s;

	s = (*tmp)->str;
	i = 0;
	result = NULL;
	
	while (s[i])
	{
		j = 0;
		if (s[i] == DOUBLE_QUOTE)
		{
			result = handel_double_q(result, s, &i, &j, env_list);
			(*tmp)->has_quotes = 1;
		}
		else if (s[i] == SINGLE_QUOTE)
			result = handel_singleq(result, s, &i, &j);
		else if (s[i] == '$')
		{
			result = ft_strjoin(result, alloc_exp(s + (++i), &i, env_list));
			i--;
		}
		else
			result = ft_strjoin(result, ft_substr(&s[i], 0, 1));
		if (result == NULL)
			return (ft_strdup(""));
		i++;
	}
	return (result);
}

int check_if_noexpand(t_lexer *tmp)
{
	if (str_chr(tmp->str, '$') == -1 || tmp->token == delimiter)
		return 1;
	// if((tmp->str[0] == '$' &&  !is_real_char(tmp->str[1])) || !ft_strcmp(tmp->str, "$?"))
	// 	return 1;
	if (tmp->str[0] == '$' && is_number(tmp->str[1]))
	{
		tmp->str = ft_substr(tmp->str, 2, ft_strlen(tmp->str));
		return 1;
	}
	return 0;
}
t_lexer *handle_options(t_lexer **tmp, t_env **env_list)
{
    char **str;
    t_lexer *tmp2;
    t_lexer *node;
    t_lexer *current;
    int i = 0;

    str = my_split(expand_str2(tmp, env_list), 32);
	if(str[1] == NULL)
	{
		(*tmp)->str = str[0];
		return *tmp;
	}
    tmp2 = (*tmp)->next;
	if(!str[i])
	{
    	(*tmp)->str = ft_strdup("");
		return *tmp;
	}
    current = *tmp;
    while (str[i])
    {
        node = ft_lstnew((*tmp)->i++);
        node->str = ft_strdup(str[i++]); 
        current->next = node; 
        current = node; 
    }
    current->next = tmp2;
	return current;
}

void handel_expanding(t_lexer **lexer, t_env **env_list)
{
	t_lexer *tmp;
	int i;
	char *vaar;
	
	tmp = *lexer;
	vaar = NULL;
	while (tmp && tmp->str)
	{
		if (check_if_noexpand(tmp))
		{
			tmp = tmp->next;
			continue;
		}
		tmp->expanded = 1;
		tmp->has_quotes = 0;
		if(!ft_strcmp("$?", tmp->str))
			vaar = ft_strdup(tmp->str);
		if (tmp->token == word)
			tmp = handle_options(&tmp, env_list);
		else
			tmp->str = expand_str2(&tmp, env_list);
		if (tmp->token != word)
			tmp->str = ft_strdup("");
		if(vaar != NULL && tmp->str == NULL)
			tmp->str = ft_strdup("0");
		if(!tmp->str && tmp->has_quotes == 1)
			tmp->str = ft_strdup("");
		else if (!tmp->str || (*tmp->str == '\0' && tmp->token == word))
		{
			i = tmp->i;
			tmp = tmp->next;
			ft_lst_remove(lexer, i);
		}
		else
			tmp = tmp->next;	
	}
}
