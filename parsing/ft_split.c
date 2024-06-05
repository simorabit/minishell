/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 21:30:15 by mal-mora          #+#    #+#             */
/*   Updated: 2024/06/05 22:10:44 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_withspaces(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}
int is_quotes(char c)
{
	return (c == DOUBLE_QUOTE || c == SINGLE_QUOTE);
}

static int count_words(char *s)
{
	int counter;
	int i;
	int q;
	int flag;
	
	flag = -1;
	q = 0;
	i = 0;
	counter = 0;
	while (s[i])
	{
		while (s[i] && is_withspaces(s[i]))
			i++;
		if (s[i] && s[i] == DOUBLE_QUOTE)
		{
			counter++;
			i++;
			q = 1;
			while (s[i] && !(s[i] == DOUBLE_QUOTE && is_withspaces(s[i + 1])))
			{
				if(s[i] == DOUBLE_QUOTE)
					q++;
				if(q % 2 == 0 && is_withspaces(s[i]))
					break;
				i++;
			}
			i++;
		}
		else if (s[i] && s[i] == SINGLE_QUOTE)
		{
			counter++;
			i++;
			q = 1;
			while (s[i] && !(s[i] == SINGLE_QUOTE && is_withspaces(s[i + 1])))
			{
				if(s[i] == SINGLE_QUOTE)
					q++;
				if(q % 2 == 0 && is_withspaces(s[i]))
					break;
				i++;
			}
			i++;
		}
		else if (s[i] && !is_withspaces(s[i]))
		{
			counter++;
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
				if (is_withspaces(s[i]) && !q)
					break;
				if (is_withspaces(s[i]) && q % 2 != 0)
					break;
				i++;
			}
		}
	}
	return (counter);
}

int is_space_after_quote(char *s, char quotes)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == quotes && (s[i + 1] && !is_withspaces(s[i + 1])))
			return (1);
		i++;
	}
	return (0);
}

static char *allocate_element(char **s, char **array, int j)
{
	int i;

	i = 0;
	if (**s == SINGLE_QUOTE)
		return (ft_word((char *)(*s), array, j, SINGLE_QUOTE));
	else if (**s == DOUBLE_QUOTE)
		return (ft_word((char *)(*s), array, j, DOUBLE_QUOTE));
	else
		return (ft_word((char *)*s, array, j, DOUBLE_QUOTE));
	return (NULL);
}

char **ft_split(char *s)
{
	char **array;
	int j;

	j = 0;
	if (!s)
		return (NULL);
	array = (char **)malloc((count_words((char *)s) + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	while (*s)
	{
		while (*s && is_withspaces(*s))
			s++;
		if (*s && !is_withspaces(*s))
		{
			array[j] = allocate_element(&s, array, j);
			if (array[j] == NULL)
				return (free(array), NULL);
			j++;
		}
		wait_till_end(&s);
	}
	array[j] = 0;
	return (array);
}
