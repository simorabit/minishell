/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_expanding.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 21:08:16 by mal-mora          #+#    #+#             */
/*   Updated: 2024/07/23 14:40:53 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*handel_singleq(char *result, char *s, int *i, int *j)
{
	int	k;

	k = ++(*i);
	while (s[*i])
	{
		if (s[*i] == SINGLE_QUOTE)
		{
			result = ft_strjoin(result, ft_substr(s, k, *j));
			break ;
		}
		(*j)++;
		(*i)++;
	}
	return (result);
}

char	*handel_double_q(char *result, char *s, int *i, int *j, t_env **env_list)
{
	int		k;
	char	*res;

	k = ++(*i);
	while (s[*i])
	{
		if (s[*i] == DOUBLE_QUOTE)
		{
			res = ft_substr(s, k, *j);
			if (!res)
				return (NULL);
			if (str_chr(res, '$') != -1)
				result = ft_strjoin(result, expand_str(res, env_list));
			else
				result = ft_strjoin(result, res);
			break ;
		}
		(*j)++;
		(*i)++;
	}
	return (result);
}
