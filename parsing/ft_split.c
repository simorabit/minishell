/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 21:30:15 by mal-mora          #+#    #+#             */
/*   Updated: 2024/05/11 18:25:58 by mal-mora         ###   ########.fr       */
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

static int allocate_element(char const **s, char **array, int j)
{
	if (**s == SingQuote)
	{
		array[j] = get_from_quotes((char *)(*s + 1), array, j, SingQuote);
		return 1;
	}
	else if (**s == DoubleQuote)
	{
		array[j] = get_from_quotes((char *)(*s + 1), array, j, DoubleQuote);
		return 2;
	}
	else
		array[j] = ft_word((char *)*s, array, j);
	return 0;
}

char **ft_split(char const *s)
{
	char **array;
	int j;
	int fquotes;

	j = 0;
	if (!s)
		return (NULL);
	array = (char **)malloc((count_words((char *)s) + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	while (*s)
	{
		fquotes = 0;
		while (*s && is_withspaces(*s))
			s++;
		if (*s && !is_withspaces(*s))
		{
			fquotes = allocate_element(&s, array, j);
			if (array[j++] == NULL)
				return (free(array), NULL);
		}
		wait_till_end(&s, fquotes);
	}
	array[j] = 0;
	return (array);
}
