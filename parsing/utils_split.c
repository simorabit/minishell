#include "minishell.h"

static void wait_for_quotes(char const **s, char quotes)
{
	(*s)++;
	while (**s && **s != quotes)
		(*s)++;
	(*s)++;
}
char *get_from_quotes(char *s, char **arr, char ind, char quotes)
{
	int i;
	char *output;
	int j;

	i = 0;
	j = 0;
	while (s[i] && s[i] != quotes)
		i++;
	output = (char *)malloc(sizeof(char) * (i));
	if (!output)
	{
		while (j < ind)
			free(arr[j++]);
		return (NULL);
	}
	i = 0;
	while (s[i] && s[i] != quotes)
	{
		output[i] = s[i];
		i++;
	}
	output[i] = '\0';

	return (output);
}
void wait_till_end(char const **s, int flag)
{
	if (flag == 1)
		wait_for_quotes(s, SingQuote);
	else if (flag == 2)
		wait_for_quotes(s, DoubleQuote);
	else
		while (**s && !is_withspaces(**s))
			(*s)++;
}
char *ft_word(char *s, char **arr, int ind)
{
	int i;
	char *output;
	int j;

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

