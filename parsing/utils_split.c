#include "minishell.h"

static void wait_for_quotes(char **s, char quotes)
{
	int qCount;

	qCount = 0;
	(*s)++;
	while (**s)
	{
		if (is_withspaces((**s)) && qCount)
			break;
		if (**s == quotes)
			qCount++;
		(*s)++;
	}
}
int get_len(char *s, char quotes)
{
	int i;
	int findq;
	
	findq = 0;
	i = 0;
	if(s[i] != quotes)
	{
		while (s[i] && !is_withspaces(s[i]))
			i++;
		return i;
	}
	i++;
	while (s[i] && !(is_withspaces(s[i]) && findq))
	{
		if(s[i] == quotes)
			findq = 1;
		i++;
	}
	return i;
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
void wait_till_end(char **s)
{
	if(**s == SingQuote)
		wait_for_quotes(s, SingQuote);
	else if(**s == DoubleQuote)
		wait_for_quotes(s, DoubleQuote);
	else
		while (**s && !is_withspaces(**s))
			(*s)++;
}
