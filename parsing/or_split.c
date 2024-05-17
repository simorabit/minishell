#include "minishell.h"

static int	count_wordss(char *s, char c)
{
	int	counter;
	int	i;

	i = 0;
	counter = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			counter++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (counter);
}

static char	*or_ft_word(char *s, char c, char **arr, int ind)
{
	int		i;
	char	*output;
	int		j;

	i = 0;
	j = 0;
	while (s[i] && (s[i] != c || s[i - 1] != c))
		i++;
	output = (char *)malloc(sizeof(char) * (i + 1));
	if (!output)
	{
		while (j < ind)
			free(arr[j++]);
		return (NULL);
	}
	i = 0;
	while (s[i] && (s[i] != c || s[i - 1] == c))
	{
		output[i] = s[i];
		i++;
	}
	output[i] = '\0';
	return (output);
}

char	**or_split(char const *s, char c)
{
	char	**array;
	int		j;

	j = 0;
	if (!s)
		return (NULL);
	array = (char **)malloc((count_wordss((char *)s, c) + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	while (*s)
	{
		if (*s && *s == c)
		{
			array[j] = or_ft_word((char *)s + 1, c, array, j);
			if (array[j] == NULL)
				(free(array),(void)NULL);
			j++;
		}
		s++;
		while (*s && (*s != c || *(s -1) == c))
			s++;
	}
	array[j] = 0;
	return (array);
}
