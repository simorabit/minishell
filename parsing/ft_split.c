/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 21:30:15 by mal-mora          #+#    #+#             */
/*   Updated: 2024/05/14 12:37:05 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_withspaces(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}
static int count_words(char *s)
{
	int counter;
	int i;

	i = 0;
	counter = 0;
	while (s[i])
	{
		while (s[i] && is_withspaces(s[i]))
			i++;
		if (s[i] && s[i++] == DoubleQuote)
		{
			counter++;
			while (s[i] && s[i] != DoubleQuote)
				i++;
			i++;
		}
		else if (s[i] && !is_withspaces(s[i]))
		{
			counter++;
			while (s[i] && !is_withspaces(s[i]))
				i++;
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
			return 1;
		i++;
	}
	return 0;
}

static char *allocate_element(char **s, char **array, int j)
{
	int i;

	i = 0;
	if (**s == SingQuote)
		return ft_word((char *)(*s), array, j, SingQuote);
	else if (**s == DoubleQuote)
		return ft_word((char *)(*s), array, j, DoubleQuote);
	else
		return ft_word((char *)*s, array, j, DoubleQuote);
	return NULL;
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
