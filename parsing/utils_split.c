/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:13:15 by mal-mora          #+#    #+#             */
/*   Updated: 2024/05/16 10:57:50 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wait_for_quotes(char **s, char quotes)
{
	int	q_count;

	q_count = 0;
	(*s)++;
	while (**s)
	{
		if (is_withspaces((**s)) && q_count)
			break ;
		if (**s == quotes)
			q_count++;
		(*s)++;
	}
}

int	get_len(char *s, char quotes)
{
	int	i;
	int	findq;

	findq = 0;
	i = 0;
	if (s[i] != quotes)
	{
		while (s[i] && !is_withspaces(s[i]))
			i++;
		return (i);
	}
	i++;
	while (s[i] && !(is_withspaces(s[i]) && findq))
	{
		if (s[i] == quotes)
			findq = 1;
		i++;
	}
	return (i);
}

char	*ft_word(char *s, char **arr, char ind, char quotes)
{
	int		i;
	char	*output;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = get_len(s, quotes);
	output = (char *)malloc(sizeof(char) * (len + 1));
	if (!output)
	{
		while (j < ind)
			free(arr[j++]);
		return (NULL);
	}
	while (i < len)
	{
		output[i] = s[i];
		i++;
	}
	output[i] = '\0';
	return (output);
}

void	wait_till_end(char **s)
{
	if (**s == SINGLE_QUOTE)
		wait_for_quotes(s, SINGLE_QUOTE);
	else if (**s == DOUBLE_QUOTE)
		wait_for_quotes(s, DOUBLE_QUOTE);
	else
		while (**s && !is_withspaces(**s))
			(*s)++;
}
