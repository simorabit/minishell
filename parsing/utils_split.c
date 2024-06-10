/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:13:15 by mal-mora          #+#    #+#             */
/*   Updated: 2024/06/10 16:47:55 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void wait_for_quotes(char **s, char quotes)
{
	(*s)++;
	int q;

	q = 1;
	while (**s && !(**s == quotes && is_withspaces(*(*s + 1))))
	{
		if (**s == quotes)
			q++;
		if (q % 2 == 0 && is_withspaces(**s))
			break;
		(*s)++;
	}
	(*s)++;
}

int get_len(char *s, char quotes)
{
	int i;
	int q;
	int flag;

	flag = -1;
	q = 0;
	i = 0;
	if (*s == quotes)
	{
		i = 1;
		q = 1;
		while (s[i] && !(s[i] == quotes && is_withspaces(s[i + 1])))
		{
			if (s[i] == quotes)
				q++;
			if (q % 2 == 0 && is_withspaces(s[i]))
				break;
			i++;
		}
	}
	else
	{
		while (s[i])
		{
			if (flag == -1 && s[i] == DOUBLE_QUOTE)
			{
				q++;
				flag = 0;
			}
			if (flag == 0 && s[i] == DOUBLE_QUOTE)
				q++;
			else if (flag == -1 && s[i] == SINGLE_QUOTE)
			{
				q++;
				flag = 1;
			}
			if (flag == 1 && s[i] == SINGLE_QUOTE)
				q++;
			if ((is_withspaces(s[i]) && !q) || (is_withspaces(s[i]) && q % 2 != 0))
				break;
			i++;
		}
	}
	return (i);
}

char *ft_word(char *s, char **arr, char ind, char quotes)
{
	int i;
	char *output;
	int j;
	int len;

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

void wait_if_char(char **s)
{
	int q;
	int flag;

	flag = -1;
	q = 0;
	while (**s)
	{
		if (flag == -1 && **s == DOUBLE_QUOTE)
		{
			q++;
			flag = 0;
		}
		if (flag == 0 && **s == DOUBLE_QUOTE)
			q++;
		else if (flag == -1 && **s == SINGLE_QUOTE)
		{
			q++;
			flag = 1;
		}
		if (flag == 1 && **s == SINGLE_QUOTE)
			q++;
		if (is_withspaces(**s) && !q)
			break;
		if (is_withspaces(**s) && q % 2 != 0)
			break;
		(*s)++;
	}
}

void wait_till_end(char **s)
{
	int q;
	int flag;

	flag = -1;
	q = 0;
	if (**s == SINGLE_QUOTE)
		wait_for_quotes(s, SINGLE_QUOTE);
	else if (**s == DOUBLE_QUOTE)
		wait_for_quotes(s, DOUBLE_QUOTE);
	else
		wait_if_char(s);
}
