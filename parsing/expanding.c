/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:35:55 by mal-mora          #+#    #+#             */
/*   Updated: 2024/05/17 12:44:25 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_real_char(char c)
{
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

char	*allocate_for_expand(char *str)
{
	int		i;
	int		len;
	char	*new_s;
	char 	*res;
	
	len = 0;
	i = 0;
	if(!str)
		return NULL;
	while (is_real_char(str[i++]))
		len++;
	new_s = malloc(len + 1);
	if (!new_s)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_s[i] = str[i];
		i++;
	}
	new_s[i] = '\0';
	res = ft_strjoin(getenv(new_s), str + ft_strlen(new_s));
	// free(new_s);
	return (res);
}

char	*expand_str(t_lexer *lexer, int dol_pos)
{
	int		i;
	char	**result;
	char	*befor_dollar;
	char	*res;
	
	if (lexer->str[0] != '$')
		befor_dollar = ft_substr(lexer->str, 0, dol_pos);
	else
		befor_dollar = ft_strdup("");
	i = 0;
	result = or_split(lexer->str + dol_pos, '$');
	
	while (result[i])
	{
		result[i] = allocate_for_expand(result[i]);
		i++;
	}
	res = ft_strjoin(befor_dollar, result[0]);
	i = 1;
	while (result[i])
	{
		res = ft_strjoin(res, result[i]);
		i++;
	}
	// 	printf("%s" ,res);
	// exit(0);
	// free(befor_dollar);
	// free_list(result);
	return (res);
}

void	*handel_expanding(t_lexer **lexer)
{
	t_lexer	*tmp;
	int		pos;
	
	tmp = *lexer;
	while (tmp)
	{
		pos = str_chr(tmp->str, '$');
		tmp->str = expand_str(tmp, pos);
		if (tmp->str == NULL)
			return NULL;
		if (*tmp->str == '\0')
			ft_lst_remove(lexer, tmp->i);
		tmp = tmp->next;
	}
	return *lexer;
}
