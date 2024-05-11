/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 21:30:15 by mal-mora          #+#    #+#             */
/*   Updated: 2024/05/11 10:33:14 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_withspaces(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}
static int	count_words(char *s)
{
	int	counter;
	int	i;

	i = 0;
	counter = 0;
	while (s[i])
	{
		while (s[i] && is_withspaces(s[i]))
			i++;
		if (s[i] && !is_withspaces(s[i]))
		{
			counter++;
			while (s[i] && !is_withspaces(s[i]))
				i++;
		}
	}
	return (counter);
}

static char	*ft_word(char *s, char **arr, int ind)
{
	int		i;
	char	*output;
	int		j;

	i = 0;
	j = 0;
	while (s[i] && !is_withspaces(s[i]))
		i++;
	output = (char *)malloc(sizeof(char) * (i + 1));
	if (!output)
	{
		while (j < ind)
			free(arr[j++]);
		return (NULL);
	}
	i = 0;
	while (s[i] && !is_withspaces(s[i]))
	{
		output[i] = s[i];
		i++;
	}
	output[i] = '\0';
	return (output);
}

char	**ft_split(char const *s)
{
	char	**array;
	int		j;

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
			array[j] = ft_word((char *)s, array, j);
			if (array[j] == NULL)
				return (free(array), NULL);
			j++;
		}
		while (*s && !is_withspaces(*s))
			s++;
	}
	array[j] = 0;
	return (array);
}

